#include "socket_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 

#define INIT_BUFFER_SIZE 16

void print_http(char* msg, int length) {
	for (int i = 0; i < length; i++)
	{
		printf("%c", msg[i]);
	}
	printf("\n");
}

bool isBufferStartsWithStr(const char *buffer, int buffer_size, const char *str)
{
	for (int i = 0; i < strlen(str); i++) {
		if (i >= buffer_size) {
			return false;
		}
		if (str[i] != buffer[i]) {
			return false;
		}
	}
	return true;
}

int countSubStrInBuffer(const char *buffer, int buffer_size, const char *str)
{
	int counter = 0;
	for (int i = 0; i < buffer_size; i++)
	{
		if (isBufferStartsWithStr(buffer+i, buffer_size - i, str)) {
			counter++;
		}
	}
	return counter;
}

bool ProcessHTTPRequest(int from_socket, int to_socket, int end_of_msg_condition) {
	int msg_len = 0;
	char *http_msg = (char *)malloc(INIT_BUFFER_SIZE);
	while (true) {
		/* read the next message recived */
		int bytes_recived = recv(from_socket, &(http_msg[msg_len]), (int)INIT_BUFFER_SIZE, 0);
		msg_len += bytes_recived;

		if (countSubStrInBuffer(http_msg, msg_len, "\r\n\r\n") >= end_of_msg_condition) {
			break;
		}

		//printf("current msg: %s\n new length: %d\n", &http_msg[0], output_len);

		/* allocate another INIT_BUFFER_SIZE to output */
		http_msg = realloc(http_msg, msg_len + INIT_BUFFER_SIZE);
		
	}
	printf("LB recived: \n");
	print_http(http_msg, msg_len);
	send(to_socket, http_msg, msg_len, 0);
	printf("LB sent: \n");
	print_http(http_msg, msg_len);
	if (NULL != http_msg) {
		free(http_msg);
	}
	return true;
}

bool ProcessAnswer(int from_socket, int to_socket, bool send_to) {
	//ProcessHTTPRequest(from_socket, to_socket, send_to);
	return true;
}