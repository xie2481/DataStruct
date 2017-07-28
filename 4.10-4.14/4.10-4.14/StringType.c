#include <string.h>
#include <stdlib.h>
#include "StringType.h"
void StrAssign(StringType* t, StringType s) {
	*t = (StringType)malloc(sizeof(char)*strlen(s));
	strcpy(*t, s);
}
int StrCompare(StringType s, StringType t) {
	return strcmp(s, t);
}
int StrLength(StringType s) {
	return strlen(s);
}
StringType Concat(StringType s, StringType t) {
	StringType p = (StringType)malloc(sizeof(char)*(strlen(s) + strlen(t)));
	strcpy(p, s);
	strcat(p, t);
	return p;
}
StringType SubString(StringType s, int start, int len) {
	if (start >= 1 && start <= StrLength(s) && len >= 0 && len <= StrLength(s) - start + 1) {
		StringType t = (StringType)malloc(sizeof(char)*len);
		int i = 0;
		start--;
		for (i = 0; i < len; i++) {
			t[i] = s[start++];
		}
		t[i] = '\0';
		return t;
	}
	else
		return NULL;
}