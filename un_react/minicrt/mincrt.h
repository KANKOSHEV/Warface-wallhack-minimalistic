#pragma once
#include <Windows.h>

void* m_memcpy(void* dest, void* src, unsigned int len);
void* m_memset(void* dest, char c, unsigned int len);
int _stdcall m_is_bad_code_ptr(FARPROC lpfn);
char* __cdecl m_strstr(const char* str1, const char* str2);
char* __cdecl m_strchr(const char* string, int ch);
int m_strcmp(const char* src, const char* dst);
char* m_strcpy(char* dest, const char* src);
unsigned m_strlen(const char* str);

