#include "socket_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 

#define INIT_BUFFER_SIZE 16
//#define SIZE_OF_EOM 4 
//const char EOM[SIZE_OF_EOM] = //Paster

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

//int countSubstrInStr(const char *str, int str_size, const char *substr, int substr_size) {
//	int count = 0;
//	int j;
//	for (int i = 0; i < str_size - substr_size; i++) {
//		for (j = 0; j < substr_size; j++) {
//			if (substr[j] != str[i + j]) {
//				break;
//			}
//		}
//		if (j == substr_size) {
//			count++;
//		}
//	}
//	//printf("current msg: %s\ncurrent count: %d\n", str, count);
//	return count;
//} //Paster

//bool isEndOfMessage(char *message, int message_size) {
//	for (int i = 0; i < message_size-SIZE_OF_EOM; i++) {
//		if (message[i] == EOM[0] &&
//			message[i + 1] == EOM[1] &&
//			message[i + 2] == EOM[2] &&
//			message[i + 3] == EOM[3]) {
//				return true;
//		}
//	}
//	return false;
//} //Paster

bool ProcessHTTPRequest(int from_socket, int to_socket, int end_of_msg_condition) {
	int msg_len = 0;
	char *http_msg = (char *)malloc(INIT_BUFFER_SIZE);
	while (true) {
		/* read the next message recived */
		int bytes_recived = recv(from_socket, &(http_msg[msg_len]), (int)INIT_BUFFER_SIZE, 0);
		msg_len += bytes_recived;// + 1; //did not work without the + 1!

		if (countSubStrInBuffer(http_msg, msg_len, "\r\n\r\n") >= end_of_msg_condition) {
			break;
		}

		//printf("current msg: %s\n new length: %d\n", &http_msg[0], output_len);

		//if (countSubstrInStr(&http_msg[0], output_len, EOM, SIZE_OF_EOM)>=end_of_msg_condition) {
		//	break;
		//}//paster

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