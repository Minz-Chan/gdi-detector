#ifndef _INJECT_H_
#define _INJECT_H_


#include <Windows.h>
#include <TlHelp32.h>


BOOL WINAPI LoadLib(DWORD dwProcessId, LPTSTR lpszLibName);

BOOL WINAPI FreeLib(DWORD dwProcessId, LPTSTR lpszLibName);


BOOL InjectDll(HANDLE hProcess, LPSTR szDllPath);


void SetCurrExePath(LPCTSTR lpszExePath);

// ȡ�õ�ǰEXE�������ļ���·��
TCHAR * GetCurrExePath();

#endif // _INJECT_H_