#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#include "stdlib.h"
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")

int main(int argc ,char **argv)
{	
	WSADATA			wsaData;
	SOCKET			SendingSocket;
	SOCKADDR_IN		ReceiverAddr;
	int				ReceiverAddrLen;
	int				port = 5150;

	ReceiverAddrLen = sizeof(ReceiverAddr);
	if (argc <= 1)
	{
		cout << "USAGE: UDPSender <receiver IP address> " << endl;
		//system("pause");
		return -1;
	}

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (SendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) == INVALID_SOCKET)
	{
		cout << "socket error " << endl;
		return -2;
	}

	ReceiverAddr.sin_family = AF_INET;
	ReceiverAddr.sin_port = htons(port);
	ReceiverAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);
	

	while (1)
	{
		char Buf[1024] = "\0";
		cout << "Input message " << endl;
		scanf("%s", Buf);
		if (strcmp(Buf,"quit") == 0)
		{
			break;
		}
		if (sendto(SendingSocket, Buf,1024, 0, (SOCKADDR *)&ReceiverAddr, ReceiverAddrLen) !=SOCKET_ERROR)
		{
			if (recvfrom(SendingSocket, Buf, sizeof(Buf), 0, (SOCKADDR *)&ReceiverAddr, &ReceiverAddrLen!=SOCKET_ERROR) )
			{
				cout << "We successfully received  :" << Buf << endl;
			}
			else
			{
				cout << "recvfrom error" << WSAGetLastError() << endl;
			}
			
		}
		else
		{
			cout << "sendto error " << WSAGetLastError()<<endl;
			return -2;
		}
	}

	closesocket(SendingSocket);
	WSACleanup();
	//cout<<"hello word!"<<endl;
	//system("pause");
	return 0;
}