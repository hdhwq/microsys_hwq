#include <iostream>
#include <winsock.h>
#include <stdio.h>

using namespace std;
#if 0
// tcp server
int main()
{
	WSADATA wsadata;
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
	while (true)
	{
		conSock = accept(listenSock, (sockaddr*)&addrCon, &len);
		if (conSock == INVALID_SOCKET)
		{
			cout << "Accept Error" << endl;
			return 0;
		}
		cout << inet_ntoa(addrCon.sin_addr) << " Connect to Server!" << endl;

	}

	closesocket(conSock);
	closesocket(listenSock);

	WSACleanup();

	return 0;
}
#endif
#if 1 
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
