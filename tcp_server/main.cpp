#include <iostream>
#include <winsock2.h>
//#include <winsock.h>
#include <stdio.h>
#include <Windows.h>
#include <ws2def.h>

using namespace std;
#if 1
// tcp server
int main()
{
	WSADATA wsadata;
	WSABUF  wsabuf;
	memset(&wsabuf, 0, sizeof(wsabuf));
	
	int ret = WSAStartup(0x0202, &wsadata);
	if (ret != 0 || 0x0202 != wsadata.wVersion)
	{
		cout << "WSAStartup Error!";
		return 0;
	}
	SOCKET listenSock = INVALID_SOCKET;
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
	{
		cout << "Create Socket Error!";
		return 0;
	}

	sockaddr_in addrBind;
	memset(&addrBind, 0, sizeof(addrBind));
	addrBind.sin_family = AF_INET;
	addrBind.sin_addr.s_addr = INADDR_ANY;
	addrBind.sin_port = htons(9000);

	ret = bind(listenSock, (sockaddr*)&addrBind, sizeof(addrBind));
	if (ret == SOCKET_ERROR)
	{
		cout << "Bind Error" << endl;
		return 0;
	}

	ret = listen(listenSock, 5);
	if (ret != 0)
	{
		cout << "Listen Error" << endl;
		return 0;
	}

	SOCKET conSock;
	sockaddr_in addrCon;
	int len = sizeof(addrCon);
	DWORD written = 0;
	DWORD n =0;
	DWORD flag=0;
	wsabuf.buf = "BYE!!!";
	struct pollfd pollfds[100];
	int i = 0;
	while (true)
	{
		conSock = accept(listenSock, (sockaddr*)&addrCon, &len);
		if (conSock == INVALID_SOCKET)
		{
			cout << "Accept Error" << endl;
			return 0;
		}
		else
		{
			pollfds[i].fd = conSock;
			pollfds[i].events = POLLIN;
			//pollfds[i].revents = 0;
			cout << " Connect to Server!" << endl;
			while (1)
			{
				ret = WSAPoll(pollfds,i+1,-1);
				{
					cout << "revent = " << pollfds[i].revents << endl;
					break;
				}
			    //ret = WSARecv(conSock, &wsabuf, 1, &n, &flag, NULL, NULL);
				//int ret = WSARecv(INVALID_SOCKET, &wsabuf, 1, &n, &flag, NULL, NULL);
				/*if (ret == SOCKET_ERROR)
				{
					cout << "Accept Error" << endl;
					getchar();
					return 0;
				}
				cout << "a" << ret << endl;
				WSASend(conSock, &wsabuf, 1, &written, 0, NULL, NULL);*/
			}
			i++;

		}
			

	}

	closesocket(conSock);
	closesocket(listenSock);

	WSACleanup();

	return 0;
}
#endif
#if 0 
//udp server
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

	sockaddr_in addrBind;
	memset(&addrBind, 0, sizeof(addrBind));
	addrBind.sin_family = AF_INET;
	addrBind.sin_addr.s_addr = INADDR_ANY;
	addrBind.sin_port = htons(9000);

	ret = bind(mySock, (sockaddr*)&addrBind, sizeof(addrBind));
	if (ret == SOCKET_ERROR)
	{
		cout << "Bind Error" << endl;
		return 0;
	}

	//set non-blocking
	int nMode = 1;
	ioctlsocket(mySock, FIONBIO, (u_long FAR*) &nMode);

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
		cout << recvchar << " from " << inet_ntoa(addrRev.sin_addr) << ":" << ntohs(addrRev.sin_port) << endl;

		sendto(mySock, recvchar, strlen(recvchar) + 1, 0, (sockaddr*)&addrRev, sizeof(sockaddr));
	}

	return 0;
}


#endif
