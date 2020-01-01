#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define LOCAL_HOST "127.0.0.1"
#define MAX_LEN_FOR_MSG 100 //Doron: INITIALIZE_BUFFER_SIZE?
#define ERROR_CODE -1

#define SERVER_PORT_FILENAME "server_port"
#define HTTP_PORT_FILENAME   "http_port"

//Doron: read about SO_REUSEADDR (last page)
void initialize_sockaddr(struct sockaddr_in *sockaddr)
{
	sockaddr->sin_family = AF_INET;
	sockaddr->sin_addr.s_addr = INADDR_ANY;
	//Doron: no port initialization here
}

int get_random_int(int min, int max)
{
	assert(max >= min);
	int range = max - min + 1;
	int random_int = rand();
	random_int = random_int % range;
	return random_int + min;
}

int bind_random_port(int socket_desc, struct sockaddr_in *sockaddr)
{
	while (true)
	{
		int rand_port_num = get_random_int(1024 + 1, 64000 - 1);
		printf("Doron: rand_port_num = %d\n", rand_port_num);
		sockaddr->sin_port = htons(rand_port_num);

		if (0 == bind(socket_desc, (struct sockaddr *)sockaddr, sizeof(*sockaddr)))
		{
			return rand_port_num;
		}
	}
}

void write_port_to_file(const int port_number, const char *file_name)
{
	FILE *f = NULL;
	f = fopen(file_name, "w");
	assert(f);
	fprintf(f, "%d", port_number);
	fclose(f);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	struct sockaddr_in server;								//Doron: struct sockaddr_in? struct sockaddr? 

	int socket_desc = socket(AF_INET, SOCK_STREAM, 0);		//Doron: what does socket_desc mean? , int->SOCKET?
	//assert(socket_desc != INVALID_SOCKET);				//Doron: -1 -> INVALID_SOCKET

	initialize_sockaddr(&server);

	//Bind
	int server_port_number = bind_random_port(socket_desc, &server);

	write_port_to_file(server_port_number, SERVER_PORT_FILENAME);

	//Listen
	listen(socket_desc, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...\n");
	int new_socket = accept(socket_desc, NULL, NULL);	// Doron: int->SOCKET?
	if (new_socket < 0)
	{
		printf("accept failed\n");
		return ERROR_CODE;
	}
	printf("Connection accepted\n");

	//send and recive:
	char buf[MAX_LEN_FOR_MSG];
	char msg[MAX_LEN_FOR_MSG] = "from VB";
	int len = MAX_LEN_FOR_MSG, bytes_recv, bytes_sent;

	bytes_sent = send(new_socket, msg, MAX_LEN_FOR_MSG, 0);
	printf("server sent the following msg: %s, %d bytes length\n", msg, bytes_sent);

	printf("Waiting for client to send something...\n");
	bytes_recv = recv(new_socket, &buf[0], len, 0);
	printf("client sent the following msg: %s, %d bytes length\n", buf, bytes_recv);
	
	return 0;
}
