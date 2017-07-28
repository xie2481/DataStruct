#pragma once
typedef char* StringType;
void StrAssign(StringType* t, StringType s);//将s的值赋给t
int StrCompare(StringType s, StringType t);//比较s和t若s>t则返回值>0, 相等返回0，小于返回值<0
int StrLength(StringType s);//返回该串的长度
StringType Concat(StringType s, StringType t);//返回由s和t联结而成的新串
StringType SubString(StringType S, int start, int len);//当1<=start<=StrLength(s）且0<=len<=StrLength(s)-start+1时
//返回s中第start个字符起长度为len的子串，否则返回空串