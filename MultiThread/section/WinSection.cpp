#include "windows.h"
#include "stdio.h"
CRITICAL_SECTION cs = { 0 };
DWORD WINAPI Thread1(LPVOID pParam)
{
	while (1)
	{
		EnterCriticalSection(&cs);
		printf("********************************\n");
		Sleep(100);
		LeaveCriticalSection(&cs);
	}
	return 0;
}

DWORD WINAPI Thread2(LPVOID pParam)
{
	while (1)
	{
		EnterCriticalSection(&cs);
		printf("--------------------------------\n");
		Sleep(100);
		LeaveCriticalSection(&cs);
	}
	return 0;
}

void Critical()
{
	InitializeCriticalSection(&cs);
	DWORD nThreadID = 0;
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, Thread1, NULL, 0, &nThreadID);
	hThread[1] = CreateThread(NULL, 0, Thread2, NULL, 0, &nThreadID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	DeleteCriticalSection(&cs);
}

int main(int argc, char* argv[])
{
	Critical();
	return 0;
}