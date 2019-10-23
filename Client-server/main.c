//Orshak Ivan, 2018

#include "Main.h"
#include "Client.h"
#include "Server.h"
#include <Windows.h>
#include <string.h>

void PrintSupport()
{
	printf("Support:\n You can launch server or "
		"client on your windows PC\n"
		"Just type: '/start&server' or "
		"'/start&client'\n '/exit' "
		"- to close the program\n");
}

int RequestHandler(char* Requests)
{
	if (Requests == NULL)
		return 1;

	if (strcmp(Requests, "/help") == 0)
	{
		PrintSupport();

		return 0;
	}

	else if (strcmp(Requests, "/start&server") == 0)
		return StartServer();

	else if (strcmp(Requests, "/start&client") == 0)
		return StartClient();

	else if (strcmp(Requests, "/exit") == 0)
		exit(0);

	return 1;
}

int main()
{
	int Error;
	char ErrorsHandler[100][100] =
	{ {"Program working correctly!"},
	{"\nInvalid request!"},
	{"\nError Winsock initialization!"},
	{"\nError creating socket!"},
	{"\nInvalid IP!"}, {"\nConnect error!"},
	{"\nError message receiving"},
	{"\nServer socket bind error!"},
	{"\nServer listening error!"},
	{"\nServer accept error!"},
	{"\nError message sending!"} };
	char Requests[50];

	SetDbgMemHooks();

	SetConsoleTitle("Launcher");

	while (1)
	{
		printf("Type '/help' for view more info\n:");
		scanf_s("%s", Requests, _countof(Requests));

		Error = RequestHandler(Requests);
		printf("%s", ErrorsHandler[Error]);

		_getch();
		system("cls");
	}

	return 0;
}
