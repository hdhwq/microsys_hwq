#include "main.h"
#if 0
#include <iostream>
#include <process.h>
#include <windows.h>
using namespace std;

BOOL b = FALSE;
long g_iData = 0;
unsigned __stdcall ThreadFun(void* par)
{
	int* pout = (int*)par;
	/*while (InterlockedExchange((unsigned long*)&b, TRUE) == TRUE)
	{
		Sleep(500);
	}*/
	InterlockedExchange((unsigned long*)&b, TRUE);
	for (int i = 0; i<3; i++)
	{
		Sleep(100);
		cout <<"a1="<< *pout << endl;
	}
	InterlockedExchange((unsigned long*)&b, FALSE);
	return 0;
}
unsigned __stdcall ThreadFun1(void* par)
{
	int* pout = (int*)par;
	int d = InterlockedExchangeAdd(&g_iData, 2);
	int i = 0;
	while (InterlockedExchange((unsigned long*)&b, TRUE) == TRUE)
	{
		printf("sleep %d\n", i++);
		Sleep(0);
	}

	cout << "d=" << d << endl;
	cout << "g_iData=" << g_iData << endl;
	 d = InterlockedExchangeAdd(&g_iData, 2);
	cout << "d=" << d << endl;
	InterlockedExchange((unsigned long*)&b, FALSE);
	return 0;
}
int main()
{
	HANDLE hThread[2];
	int a1 = 3;
	int a2 = 5;

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, &ThreadFun, &a1, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, &ThreadFun1, &a2, 0, NULL);
	//等待所有线程结�?
	WaitForMultipleObjects(2, hThread, true, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	system("PAUSE");
	return 0;
}
#endif
#if 0
#include <stdio.h>  
#include <windows.h>  
#include <process.h>
volatile long g_nLoginCount; //登录次数  
DWORD __stdcall ThreadFun(void *pPM); //线程函数  

const int THREAD_NUM = 100;//启动线程�? 

DWORD WINAPI ThreadFun(void *pPM)
{
	Sleep(100); //some work should to do  
	//g_nLoginCount++;
	InterlockedIncrement((LONG *)&g_nLoginCount);
	Sleep(50);
	return 0;
}
int main()
{
	printf("     原子操作 Interlocked系列函数的使用\n");
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");

	//重复20次以便观察多线程访问同一资源时导致的冲突  
	int num = 20;
	while (num--)
	{
		g_nLoginCount = 0;
		int i;
		HANDLE  handle[THREAD_NUM];
		for (i = 0; i < THREAD_NUM; i++)
			handle[i] = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);
			//handle[i] = _beginthreadex(NULL, 0, ThreadFun, NULL, 0, NULL);
		// 由于WaitForMultipleObjects()对等待的序列有最大限制，所以采用分批等待，避免调用出错�?
		int thread_num = THREAD_NUM;
		while (thread_num > MAXIMUM_WAIT_OBJECTS)
		{	
			WaitForMultipleObjects(MAXIMUM_WAIT_OBJECTS, handle, TRUE, INFINITE);
			thread_num = THREAD_NUM - MAXIMUM_WAIT_OBJECTS;
		}
		WaitForMultipleObjects(thread_num, handle, TRUE, INFINITE);
		printf("�?d个用户登录后记录结果�?d\n", THREAD_NUM, g_nLoginCount);
	}
	return 0;
}

#endif

#if 0
//malloc最大内�?测试程序

#include <stdio.h>
#include <stdlib.h>

unsigned int max = 0;

int main()
{
	unsigned int blocksize[] = { 1024 * 1024, 1024, 1 };
	int i, count;
	for (i = 0; i < 3; i++)
	{
		for (count = 1; ; count++)
		{
			void* block = malloc(max + blocksize[i] * count);
			if (block)  //malloc ok
			{
				max += blocksize[i] * count;
				free(block);
			}
			else
			{
				break;
			}
		}
	}
	printf("max malloc size = %uB\n", max);
	return 0;
}
#endif
#if 0
// 多线程测试共享资源脏�?
#include <stdio.h>  
#include <windows.h>  
volatile long g_nLoginCount;           //登录次数  
DWORD __stdcall Fun(void *pPM);         //线程函数  
const DWORD THREAD_NUM = 50;           //启动线程�? 
DWORD WINAPI ThreadFun(void *pPM)
{
	Sleep(100); //some work should to do  
	g_nLoginCount++;
	Sleep(50);
	return 0;
}
int main()
{
	printf("     原子操作 Interlocked系列函数的使用\n");
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");

	//重复20次以便观察多线程访问同一资源时导致的冲突  
	int num = 20;
	while (num--)
	{
		g_nLoginCount = 0;
		int i;
		HANDLE  handle[THREAD_NUM];
		for (i = 0; i < THREAD_NUM; i++)
			handle[i] = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);
		WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);
		printf("�?d个用户登录后记录结果�?d\n", THREAD_NUM, g_nLoginCount);
	}
	getchar();
	return 0;
}
#endif

#if 0
#include <iostream>
#include <process.h>
#include <windows.h>
using namespace std;

BOOL b = FALSE;
unsigned __stdcall ThreadFun(void* par)
{
	int* pout = (int*)par;
	while (InterlockedExchange((unsigned long*)&b, TRUE) == TRUE)
	{
		Sleep(500);
	}
	for (int i = 0; i<3; i++)
	{
		Sleep(1000);
		cout << *pout << endl;
	}
	InterlockedExchange((unsigned long*)&b, FALSE);
	return 0;
}
int main()
{
	HANDLE hThread[2];
	int a1 = 1;
	int a2 = 2;
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, &ThreadFun, &a1, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, &ThreadFun, &a2, 0, NULL);
	//等待所有线程结�?
	WaitForMultipleObjects(2, hThread, true, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	system("PAUSE");
	return 0;
}
#endif

#if 0 
//tcp client
using namespace std;

int main()
{
	WSADATA wsadata;
	int ret = WSAStartup(0x0202, &wsadata);
	if (ret != 0 || 0x0202 != wsadata.wVersion)
	{
		cout << "WSAStartup Error!";
		return 0;
	}
	SOCKET mySock = INVALID_SOCKET;
	mySock = socket(AF_INET, SOCK_STREAM, 0);
	if (mySock == INVALID_SOCKET)
	{
		cout << "Create Socket Error!";
		return 0;
	}

	sockaddr_in addrDest;
	memset(&addrDest, 0, sizeof(addrDest));
	addrDest.sin_family = AF_INET;
	addrDest.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrDest.sin_port = htons(9000);

	ret = connect(mySock, (sockaddr*)&addrDest, sizeof(addrDest));
	if (ret == -1)
	{
		cout << GetLastError() << endl;
		getchar();
		return 0;
	}

	cout << "Connect to Server Success!" << endl;


	sockaddr_in addrMy;
	memset(&addrMy, 0, sizeof(addrMy));
	int len = sizeof(addrMy);

	ret = getsockname(mySock, (sockaddr*)&addrMy, &len);
	if (ret != 0)
	{
		cout << "Getsockname Error!" << endl;
		return 0;
	}

	cout << "Current Socket IP:" << inet_ntoa(addrMy.sin_addr) << ":" << ntohs(addrMy.sin_port) << endl;

	getchar();

	closesocket(mySock);
	WSACleanup();

	return 0;
}
#endif

#if 0
// udp client
using namespace std;
int main()
{
	WSADATA wsadata;
	int ret = WSAStartup(0x0202, &wsadata);
	if (ret != 0 || 0x0202 != wsadata.wVersion)
	{
		cout << "WSAStartup Error!";
		return 0;
	}
	SOCKET mySock = INVALID_SOCKET;
	mySock = socket(AF_INET, SOCK_DGRAM, 0);
	if (mySock == INVALID_SOCKET)
	{
		cout << "Create Socket Error!";
		return 0;
	}

	sockaddr_in addrDest;
	memset(&addrDest, 0, sizeof(addrDest));
	addrDest.sin_family = AF_INET;
	addrDest.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrDest.sin_port = htons(9000);


	//set non-blocking
	int nMode = 1;
	ioctlsocket(mySock, FIONBIO, (u_long FAR*) &nMode);

	char sendchar[20];
	strcpy_s(sendchar, "login");

	sendto(mySock, sendchar, strlen(sendchar) + 1, 0, (sockaddr*)&addrDest, sizeof(sockaddr));

	//get send socket ip
	sockaddr_in addrMy;
	memset(&addrMy, 0, sizeof(addrMy));
	int leng = sizeof(addrMy);

	ret = getsockname(mySock, (sockaddr*)&addrMy, &leng);
	if (ret != 0)
	{
		cout << "Getsockname Error!" << endl;
		return 0;
	}

	cout << "Current Socket IP:" << inet_ntoa(addrMy.sin_addr) << ":" << ntohs(addrMy.sin_port) << endl;

	char recvchar[20];
	sockaddr_in addrRev;
	memset(&addrRev, 0, sizeof(addrRev));
	memset(recvchar, 0, 20);
	int len = sizeof(sockaddr);
	while (true)
	{
		if (recvfrom(mySock, recvchar, 20, 0, (sockaddr*)&addrRev, &len) == SOCKET_ERROR)
		{
			if (GetLastError() == WSAEWOULDBLOCK || GetLastError() == 10054)
			{
				continue;
			}
			else
			{
				cout << "Receive Error!" << GetLastError() << endl;
				return 0;
			}
		}

		cout << "login success!" << endl;

		//get send socket ip
		sockaddr_in addrMy;
		memset(&addrMy, 0, sizeof(addrMy));
		int leng = sizeof(addrMy);

		ret = getsockname(mySock, (sockaddr*)&addrMy, &leng);
		if (ret != 0)
		{
			cout << "Getsockname Error!" << endl;
			return 0;
		}

		cout << "Current Socket IP:" << inet_ntoa(addrMy.sin_addr) << ":" << ntohs(addrMy.sin_port) << endl;
	}

	return 0;
}
#endif

#if 1

int main()
{
	int send_buffer_size = 2048;
	int size = 2 ;

	//send_buffer_size += ((size + 1023) >> 10) << 10;
	send_buffer_size += 2 * 1024 * 1024;
	printf("%d\n", send_buffer_size);
	getchar();
	return 0;
}
#endif
