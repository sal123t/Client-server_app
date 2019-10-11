//Orshak Ivan, 2018

#include "Main.h"
#include "Server.h"
#include <WinSock2.h> 

#pragma comment( lib, "Ws2_32.lib" )

int ServerHandler(char* Buff)
{
	if (Buff == NULL)
		return 6;

	if (strcmp(Buff, "1") == 0)
	{
		printf("Now system will be shutted down!\n");
		system("pause");
		system("shutdown /s");
	}

	else if (strcmp(Buff, "2") == 0)
	{
		printf("Now system will be rebooted!\n");
		system("pause");
		system("shutdown /r");
	}

	else if (strcmp(Buff, "4") == 0)
	{
		printf("Finishing session\n");
		system("pause");
	}

	else
	{
		printf("Trying to make command %s...\n", Buff);
		system(Buff);
	}

	return 0;
}

int StartServer()
{
	char Buff[1024] = { 0 };
	SOCKADDR_IN Client_Addr;
	int Client_Addr_Size = sizeof(Client_Addr);
	SOCKET Client_Socket;
	SOCKADDR_IN Local_Addr;
	int Port;
	SOCKET S;

	SetConsoleTitle("Server");

	if (WSAStartup(MAKEWORD(2, 2), (WSADATA*)& Buff[0]) != 0)
		return 2;

	if ((S = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		WSACleanup();

		return 3;
	}

	printf("\nType port:");
	scanf("%d", &Port);

	Local_Addr.sin_family = AF_INET;
	Local_Addr.sin_port = htons(Port);
	Local_Addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(S, (SOCKADDR*)& Local_Addr, sizeof(Local_Addr)) != 0)
	{
		closesocket(S);
		WSACleanup();

		return 7;
	}

	if (listen(S, SOMAXCONN))
	{
		closesocket(S);
		WSACleanup();

		return 8;
	}

	printf("\nWaiting connection...\n");

	if ((Client_Socket = accept(S, (SOCKADDR*)& Client_Addr, &Client_Addr_Size)) < 0)
	{
		closesocket(S);
		WSACleanup();

		return 9;
	}

	else
		printf("Connected with: %s\n", inet_ntoa(Client_Addr.sin_addr));

	while (1)
	{
		if (recv(Client_Socket, Buff, sizeof(Buff), 0) == SOCKET_ERROR)
		{
			closesocket(Client_Socket);
			closesocket(S);
			WSACleanup();

			return 6;
		}

		ServerHandler(Buff);

		if (strcmp(Buff, "4") == 0)
		{
			closesocket(Client_Socket);
			closesocket(S);
			WSACleanup();

			return 0;
		}
	}

	closesocket(Client_Socket);
	closesocket(S);
	WSACleanup();
	_getch();

	return 0;
}