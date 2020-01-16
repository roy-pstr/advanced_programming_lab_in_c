#include <stdio.h>
#include <stdlib.h>

#include "socket_tools.h"
#include "utils.h"

#define MIN_PORT 1025
#define MAX_PORT 63999
#define INIT_BUFFER_SIZE 16

void print_http_request(char *msg, int length)
{
  for (int i = 0; i < length; i++) {
    printf("%c", msg[i]);
  }
  printf("\n");
}

bool ProcessHTTPRequest(int from_socket, int to_socket, int end_contdition)
{
  int msg_len = 0;
  char *http_msg = (char *)malloc(INIT_BUFFER_SIZE);
  while (true) {
    int bytes_recived = recv(from_socket, &(http_msg[msg_len]), (int)INIT_BUFFER_SIZE, 0);
    msg_len += bytes_recived;

    if (countSubStrInBuffer(http_msg, msg_len, "\r\n\r\n") >= end_contdition) {
      break;
    }
    http_msg = realloc(http_msg, msg_len + INIT_BUFFER_SIZE);
  }

  send(to_socket, http_msg, msg_len, 0);
  if (NULL != http_msg) {
    free(http_msg);
  }
  return true;
}

int acceptHTTPClient(int http_socket)
{
  int accepted_http_socket = accept(http_socket, NULL, NULL);
  return accepted_http_socket;
}

void initialize_sockaddr(struct sockaddr_in *sockaddr)
{
  sockaddr->sin_family = AF_INET;
  sockaddr->sin_addr.s_addr = INADDR_ANY;
}

int bind_random_port(int socket, struct sockaddr_in *sockaddr)
{
  while (true) {
    int rand_port_num = get_random_int(MIN_PORT, MAX_PORT);
    sockaddr->sin_port = htons(rand_port_num);
    if (0 == bind(socket, (struct sockaddr *)sockaddr, sizeof(*sockaddr))) {
      return rand_port_num;
    }
  }
}
