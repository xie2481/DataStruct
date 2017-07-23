#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void printPerformance(char* s) {
	char op[100];
	int top = -1, i = 0;
	while (s[i] != '\0') {
		if ((s[i] >= 'a'&&s[i] <= 'z') || (s[i] >= 'A'&&s[i] <= 'Z')) {
			printf("%c", s[i]);
		}
		else if (top == -1 ||
			((op[top] == '+' || op[top] == '-') && (s[i] == '*' || s[i] == '/'))) {//当前符号的优先级高于栈顶元素
			op[++top] = s[i];
		}
		else if(((op[top] == '*' || op[top] == '/') && (s[i] == '+' || s[i] == '-'))||
			op[top] == s[i] ||
			(((op[top]=='+'||op[top] == '-') && (s[i] == '-' || s[i] == '+')))||
			(((op[top]=='*'||op[top] == '/') && (s[i] == '*' || s[i] == '/')))) {//当前符号的优先级低于栈顶元素
			printf("%c", op[top--]);
			i--;
		}
		i++;
	}
	while (top != -1) {
		printf("%c", op[top--]);
	}
}
int getResult(char* s) {
	char op[100];
	int number[100];
	int top1 = -1,top2=-1, i = 0;
	while (s[i] != '\0') {
		if (s[i] >= '0'&&s[i]<='9') {
			number[++top2] = s[i]-'0';
		}
		else if (top1 == -1 ||
			((op[top1] == '+' || op[top1] == '-') && (s[i] == '*' || s[i] == '/'))) {//当前优先级高于栈顶元素
			op[++top1] = s[i];
		}
		else if (((op[top1] == '*' || op[top1] == '/') && (s[i] == '+' || s[i] == '-')) ||
			op[top1] == s[i] ||
			(((op[top1] == '+' || op[top1] == '-') && (s[i] == '-' || s[i] == '+'))) ||
			(((op[top1] =='*'|| op[top1] == '/') && (s[i] == '*' || s[i] == '/')))) {//当前优先级低于栈顶元素
			int b = number[top2--];
			int a = number[top2--];
			if (op[top1] == '+')
				number[++top2] = a + b;
			else if (op[top1] == '-')
				number[++top2] = a - b;
			else if (op[top1] == '*')
				number[++top2] = a*b;
			else
				number[++top2] = a / b;
			top1--;
			i--;
		}
		i++;
	}
	while (top1 != -1) {
		int b = number[top2--];
		int a = number[top2--];
		if (op[top1] == '+')
			number[++top2] = a + b;
		else if (op[top1] == '-')
			number[++top2] = a - b;
		else if (op[top1] == '*')
			number[++top2] = a*b;
		else
			number[++top2] = a / b;
		top1--;
	}
	return number[top2--];
}
int justifyIsPoly(char* result,char* s,int low,int high) {
	if (low <= high) {
		if (low < high) {//当前不是叶子节点
			if (s[high] >= 'a'&&s[high] <= 'z') {
				return 0;
			}
			else {
				int length=strlen(result);
				result[length] = s[high];
				result[length + 1] = '\0';
				if (justifyIsPoly(result, s, low,low)
					&& justifyIsPoly(result, s, low+1,high-1)) {
					return 1;
				}
				else
					return 0;
			}
		}
		else {//当前是叶子节点
			if (s[high] >= 'a'&&s[high] <= 'z') {
				int length = strlen(result);
				result[length] = s[high];
				result[length +1] = '\0';
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	else {
		return 0;
	}
}
int main() {
	char s[100],result[100];
	int top =-1,i=0;
	gets(s);
	//printPerformance(s);
	//printf("\n");
	//printf("%d", getResult(s));
	result[0] = '\0';
	if (justifyIsPoly(result, s, 0, strlen(s) - 1))
		puts(result);
	else
		printf("不合法");
	return 0;
}