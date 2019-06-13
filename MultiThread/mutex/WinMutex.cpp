// WinMutex.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "windows.h"
#include "stdio.h"
HANDLE g_hMutex = 0;//接收互斥句柄

DWORD WINAPI TestProc1(LPVOID pParam)
{
	while (1)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		printf("********************************\n");
		Sleep(100);
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

DWORD WINAPI TestProc2(LPVOID pParam)
{
	while (1)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		printf("--------------------------------\n");
		Sleep(100);
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

void Mutex()
{
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	DWORD nThreadID = 0;
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, TestProc1, NULL, 0, &nThreadID);
	hThread[1] = CreateThread(NULL, 0, TestProc2, NULL, 0, &nThreadID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(g_hMutex);
}

int main(int argc, char* argv[])
{
	Mutex();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
