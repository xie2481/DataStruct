#pragma once
typedef char* StringType;
void StrAssign(StringType* t, StringType s);//��s��ֵ����t
int StrCompare(StringType s, StringType t);//�Ƚ�s��t��s>t�򷵻�ֵ>0, ��ȷ���0��С�ڷ���ֵ<0
int StrLength(StringType s);//���ظô��ĳ���
StringType Concat(StringType s, StringType t);//������s��t������ɵ��´�
StringType SubString(StringType S, int start, int len);//��1<=start<=StrLength(s����0<=len<=StrLength(s)-start+1ʱ
//����s�е�start���ַ��𳤶�Ϊlen���Ӵ������򷵻ؿմ�