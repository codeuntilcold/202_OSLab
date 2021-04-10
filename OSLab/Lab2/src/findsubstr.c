#include "findsubstr.h"

int find_sub_string(const char* str, const char* sub)
{
	char* pS = (char*)str;
	char* ps = (char*)sub;
	while (*pS != '\0')
	{
		if (*ps != *pS) ps = (char*)sub;
		if (*ps == *pS) ps++;
		pS++;
		if (*ps == '\0') return (pS - str) - (ps - sub);
	}
	return -1;
}