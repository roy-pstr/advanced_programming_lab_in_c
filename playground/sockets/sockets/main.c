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

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_desc == -1)
	{
		printf("Could not create socket");
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
	puts("Waiting for incoming connections.../n");
	new_socket = accept(socket_desc, NULL, NULL);
	if (new_socket != 0)
	{
		perror("accept failed\n");
	}

	puts("Connection accepted\n");
	return 0;
}