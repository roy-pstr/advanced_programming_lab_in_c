//#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
//#include <sys/socket.h> 
#include <winsock.h>
//#include <WS2tcpip.h>
//#pragma comment(lib,"Ws2_32.lib")

#define LOCAL_HOST "127.0.0.1"
#define PORT 8888

int main(int argc, char *argv[])
{
	int socket_desc, new_socket;
	struct sockaddr_in server;

	WSADATA wsaData;
	int StartupRes = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (StartupRes != NO_ERROR)
	{
		printf("error %ld at WSAStartup( ), ending program.\n", WSAGetLastError());
		// Tell the user that we could not find a usable WinSock DLL.                                  
		return 5555;
	}


	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
		return 55555;
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(LOCAL_HOST);
	server.sin_port = htons(PORT);

	//Bind
	if (bind(socket_desc, (SOCKADDR*)&server, sizeof(server))!=0)
	{
		puts("bind failed\n");
	}
	puts("bind done\n");

	//Listen
	listen(socket_desc, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...\n");
	new_socket = accept(socket_desc, NULL, NULL);
	if (new_socket != 0)
	{
		perror("accept failed\n");
	}

	puts("Connection accepted\n");
	return 0;
}