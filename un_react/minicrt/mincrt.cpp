#include "mincrt.h"

extern "C" int _fltused = 0;
#pragma data_seg()
#pragma comment(linker, "/merge:.CRT=.rdata")

void* m_memcpy(void* dest, void* src, unsigned int len)
{
	unsigned int i;
	char * char_src = (char *)src;
	char * char_dest = (char *)dest;
	for (i = 0; i < len; i++) {
		char_dest[i] = char_src[i];
	}
	return dest;
}
void* m_memset(void* dest, char c, unsigned int len)
{
	unsigned int i;
	unsigned int fill;
	unsigned int chunks = len / sizeof(fill);
	char * char_dest = (char *)dest;
	unsigned int * uint_dest = (unsigned int *)dest;
	fill = (c << 24) + (c << 16) + (c << 8) + c;

	for (i = len; i > chunks * sizeof(fill); i--) {
		char_dest[i - 1] = c;
	}

	for (i = chunks; i > 0; i--) {
		uint_dest[i - 1] = fill;
	}

	return dest;
}
int _stdcall m_is_bad_read_ptr(const void* lp, unsigned int ucb)
{
	return (ucb && (!lp || (char*)lp + ucb - 1 < lp));
}
int _stdcall m_is_bad_code_ptr(FARPROC lpfn)
{
	return m_is_bad_read_ptr(lpfn, 1u);
}
char* __cdecl m_strstr(const char* str1, const char* str2)
{
	char *cp = (char *)str1;
	char *s1, *s2;

	if (!*str2)
		return((char *)str1);

	while (*cp)
	{
		s1 = cp;
		s2 = (char *)str2;

		while (*s1 && *s2 && !(*s1 - *s2))
			s1++, s2++;

		if (!*s2)
			return(cp);

		cp++;
	}

	return(0);
}
char* __cdecl m_strchr(const char* string, int ch) 
{
	while (*string && *string != (char)ch)
		string++;
	if (*string == (char)ch)
		return((char*)string);
	return(NULL);
}
int m_strcmp(const char* src, const char* dst)
{
	int ret = 0;
	unsigned char *p1 = (unsigned char *)src;
	unsigned char *p2 = (unsigned char *)dst;
	while (!(ret = *p1 - *p2) && *p2) 
		++p1, ++p2;

	if (ret < 0)
		ret = -1;
	else if (ret > 0)
		ret = 1;

	return ret;
}
char* m_strcpy(char* dest, const char* src)
{
	char *ret = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return ret;
}
unsigned m_strlen(const char* str)
{
	int cnt = 0;
	if (!str)
		return 0;
	for (; *str != '\0'; ++str)
		++cnt;
	return cnt;
}
