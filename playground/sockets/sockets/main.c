#include "socket_tools.h"
#include <assert.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#define LOCAL_HOST "127.0.0.1"
#define ERROR_CODE -1

#define SERVER_PORT_FILENAME "server_port"
#define HTTP_PORT_FILENAME "http_port"

#define MIN_PORT 1025
#define MAX_PORT 63999

#define COMPUTER_NUM 3

void initialize_sockaddr(struct sockaddr_in *sockaddr)
{
  sockaddr->sin_family = AF_INET;
  sockaddr->sin_addr.s_addr = INADDR_ANY;
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
  while (true) {
    int rand_port_num = get_random_int(MIN_PORT, MAX_PORT);
    sockaddr->sin_port = htons(rand_port_num);
    if (0 == bind(socket, (struct sockaddr *)sockaddr, sizeof(*sockaddr))) {
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

int acceptHTTPClient(int http_socket)
{
  int accepted_http_socket = accept(http_socket, NULL, NULL);
  return accepted_http_socket;
}

int main()
{
  srand(time(NULL));

  struct sockaddr_in server_address;
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  initialize_sockaddr(&server_address);
  int server_port_number = bind_random_port(server_socket, &server_address);
  write_port_to_file(server_port_number, SERVER_PORT_FILENAME);
  listen(server_socket, COMPUTER_NUM);

  struct sockaddr_in http_address;
  int http_socket = socket(AF_INET, SOCK_STREAM, 0);
  initialize_sockaddr(&http_address);
  int http_port_number = bind_random_port(http_socket, &http_address);
  write_port_to_file(http_port_number, HTTP_PORT_FILENAME);
  listen(http_socket, 1);

  int accepted_server_sockets[COMPUTER_NUM];
  for (int i = 0; i < COMPUTER_NUM; i++) {
    accepted_server_sockets[i] = accept(server_socket, NULL, NULL);
  }

  int http_connection;
  int curr_server_ind = 0;
  while (true) {
    curr_server_ind %= COMPUTER_NUM;
    http_connection = acceptHTTPClient(http_socket);

    ProcessHTTPRequest(http_connection, accepted_server_sockets[curr_server_ind], 1);

    ProcessHTTPRequest(accepted_server_sockets[curr_server_ind], http_connection, 2);

    curr_server_ind++;
  }

  return 0;
}
