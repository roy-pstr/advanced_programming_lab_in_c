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

#define MIN_PORT 1025
#define MAX_PORT 63999

#define COMPUTER_NUM 3

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

int bind_random_port(int socket, struct sockaddr_in *sockaddr)
{
	while (true)
	{
		int rand_port_num = get_random_int(MIN_PORT, MAX_PORT);
		printf("Doron: rand_port_num = %d\n", rand_port_num);
		sockaddr->sin_port = htons(rand_port_num);
		if (0 == bind(socket, (struct sockaddr *)sockaddr, sizeof(*sockaddr)))
		{
			return rand_port_num;
		}
	}
}

void write_port_to_file(int port_number, const char *file_name)
{
	FILE *f = NULL;
	f = fopen(file_name, "w");
	assert(f);
	fprintf(f, "%d\n", port_number);
	fclose(f);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	struct sockaddr_in server_address;
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);		// Doron: int->SOCKET?
	initialize_sockaddr(&server_address);
	int server_port_number = bind_random_port(server_socket, &server_address);
	write_port_to_file(server_port_number, SERVER_PORT_FILENAME);
	listen(server_socket, COMPUTER_NUM);

	struct sockaddr_in http_address;
	int http_socket = socket(AF_INET, SOCK_STREAM, 0);			 // Doron: int->SOCKET?
	initialize_sockaddr(&http_address);
	int http_port_number = bind_random_port(http_socket, &http_address);
	write_port_to_file(http_port_number, HTTP_PORT_FILENAME);
	listen(http_socket, 1);


	//Accept and incoming connection
	printf("Waiting for incoming connections...\n");
	int accepted_server_sockets[COMPUTER_NUM];
	for (int i = 0; i < COMPUTER_NUM; i++)
	{
		accepted_server_sockets[i] = accept(server_socket, NULL, NULL);
		if (accepted_server_sockets[i] < 0)						 //Doron: this block will be removed
		{
			printf("accept failed\n");
			return ERROR_CODE;
		}
		printf("Server connection #%d accepted\n", i+1);
	}

	int accepted_http_socket = accept(http_socket, NULL, NULL);
	if (accepted_http_socket < 0)								//Doron: this block will be removed
	{
		printf("accept failed\n");
		return ERROR_CODE;
	}
	printf("HTTP connection accepted\n");





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
