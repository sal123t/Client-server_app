//Orshak Ivan, 2018

#include "Main.h"
#include "Client.h"
#include <WinSock2.h>

#pragma comment( lib, "Ws2_32.lib" )

int StartClient()
{
	char Buff[1024] = { 0 };
	SOCKADDR_IN Dest_Addr;
	int Port;
	SOCKET S;
	char ServerAddr[20];

	SetConsoleTitle("Client");

	if (WSAStartup(MAKEWORD(2, 2), (WSADATA*)& Buff[0]) != 0)
		return 2;

	if ((S = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		WSACleanup();

		return 3;
	}

	printf("Type IP of server:");
	scanf_s("%s", ServerAddr, _countof(ServerAddr));
	printf("\nType port:");
	scanf("%d", &Port);

	Dest_Addr.sin_family = AF_INET;
	Dest_Addr.sin_port = htons(Port);

	if (inet_addr(ServerAddr) != INADDR_NONE)
		Dest_Addr.sin_addr.s_addr = inet_addr(ServerAddr);
	else
	{
		closesocket(S);
		WSACleanup();

		return 4;
	}

	if (connect(S, (SOCKADDR*)& Dest_Addr, sizeof(Dest_Addr)) != 0)
	{
		closesocket(S);
		WSACleanup();

		return 5;
	}

	printf("Connected with: %s\n", ServerAddr);
	system("pause");

	while (1)
	{
		system("cls");
		printf("Working on %s server\n"
			"1 - shutdown server\n"
			"2 - reboot server\n"
			"3 - make console command\n"
			"4 - finish work\n", ServerAddr);

		switch (_getch())
		{
		case '1':
			if (send(S, "1", sizeof("1"), 0) == SOCKET_ERROR)
			{
				closesocket(S);
				WSACleanup();

				return 10;
			}
			break;

		case '2':
			if (send(S, "2", sizeof("2"), 0) == SOCKET_ERROR)
			{
				closesocket(S);
				WSACleanup();

				return 10;
			}
			break;

		case '3':
			printf("Enter command: ");
			scanf("%s", Buff);
			if (send(S, Buff, sizeof(Buff), 0) == SOCKET_ERROR)
			{
				closesocket(S);
				WSACleanup();

				return 10;
			}
			break;

		case '4':
			if (send(S, "4", sizeof("4"), 0) == SOCKET_ERROR)
			{
				closesocket(S);
				WSACleanup();

				return 10;
			}
			else
			{
				closesocket(S);
				WSACleanup();

				return 0;
			}

		default:
			printf("Unknown command!\n");
			continue;
		}
	}

	closesocket(S);
	WSACleanup();

	_getch();

	return 0;
}