#include <stdio.h>
#include <stdlib.h>
#include "StringType.h"
StringType traverse(StringType s) {
	int i = 0, len = StrLength(s),high=len-1;
	StringType t = (StringType)malloc(sizeof(char)*len);
	for (i = 0; i < len; i++) {
		t[i] = s[high--];
	}
	t[i] = '\0';
	return t;
}
StringType getStringInsNott(StringType s, StringType t,int** poisition) {//求得在s中不在t中的字符，并且返回相应的位置
	int i = 0, j = 0, len1 = StrLength(s), len2 = StrLength(t), k = 0;;
	StringType p = (StringType)malloc(sizeof(char)*(len1 + len2));
	*poisition = (int*)malloc(sizeof(int)*(len1 + len2));
	for (i = 0; i < len1; i++) {
		for (j = 0; j < len2; j++) {
			if (s[i] == t[j]) {
				break;
			}
		}
		if (j == len2) {//该字符不在t中
			p[k] = s[i];
			(*poisition)[k++] = i;
		}
	}
	p[k] = '\0';
	return p;
}
void Replace(StringType* s, StringType t, StringType v) {
	int i = 0, lenT=StrLength(t),lenV=StrLength(v);
	while ((*s)[i] != '\0'&&i+lenT<=StrLength(*s)) {
		StringType p = SubString(*s, i + 1, lenT);
		if (StrCompare(p, t) == 0) {//替换当前子串
			if ((*s)[i + lenT] == '\0') {//待替换子串恰好在末尾
				*s = SubString(*s, 1, i);
				*s = Concat(*s, v);
				break;
			}
			StringType temp = SubString(*s, i + 1 + lenT, StrLength(*s) - i - lenT);//得到匹配子串之后的子串
			temp = Concat(v, temp);
			*s = Concat(SubString(*s, 1, i),temp);
			i +=lenV;
		}
		else
			i++;
	}
}
void Delete(StringType* s, StringType t) {
	int i = 0,len=StrLength(t);
	while ((*s)[i] != '\0'&&i+len<=StrLength(*s)) {
		StringType p = SubString(*s, i + 1, len);
		if (StrCompare(p, t) == 0) {
			if ((*s)[i + len] == '\0') {//当前待删除串恰好在末尾
				*s = SubString(*s, 1, i);
				break;
			}
			else {
				StringType temp = SubString(*s, i + 1 + len, StrLength(*s) - i - len);
				*s = Concat(SubString(*s, 1, i), temp);
			}
		}
		i++;
	}
}
StringType change(StringType s) {//前缀转后缀,方便起见，操作数全部设为字母
	StringType stack = (StringType)malloc(sizeof(char)*StrLength(s));
	stack[0] = '\0';
	int top =0,i=1,len=StrLength(s),end=0;
	while (top < len-1) {
		while (s[i]<'a' || s[i]>'z')
			i++;
		stack[top++] = s[i];
		if (i+1<len&&s[i + 1] >= 'a'&&s[i + 1] <= 'z') {
			stack[top++] = s[i + 1];
			int j = i - 1;
			while (j > end) {
				if (s[j] > 'z' || s[j] < 'a')
					stack[top++] = s[j];
				j--;
			}
			end = i;
			i++;
		}
		i++;
	}
	stack[top++] = s[0];
	stack[top] = '\0';
	return stack;
}
int main() {
	StringType s = "dasqwecqwec";
	StringType t = "qwec";
	StringType ex = "+*a+eg+cd";
	//printf("%s",Concat(SubString(s,1,0),Concat("@", SubString(s, 0 + 1 + 3, StrLength(s) - 0 - 3))));
	int* poisition,i=0,len=0;
	StringType p = getStringInsNott(s, t,&poisition);
	len = StrLength(p);
	printf("%s\n", p);
	for (i = 0; i < len; i++) {
		printf("%d\t", poisition[i]);
	}
	printf("\n");
	Replace(&s, t, "$");
	printf("%s\n", s);
	Delete(&s, t);
	printf("%s\n", s);
	printf("%s\n", change(ex));
	return 0;
}