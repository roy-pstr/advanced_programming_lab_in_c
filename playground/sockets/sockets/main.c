#include "socket_tools.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SERVER_PORT_FILENAME "server_port"
#define HTTP_PORT_FILENAME "http_port"
#define SERVERS_NUM 3

int main()
{
  initialize_random();

  struct sockaddr_in server_address;
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  initialize_sockaddr(&server_address);
  int server_port_number = bind_random_port(server_socket, &server_address);
  write_int_to_file(server_port_number, SERVER_PORT_FILENAME);
  listen(server_socket, SERVERS_NUM);

  struct sockaddr_in http_address;
  int http_socket = socket(AF_INET, SOCK_STREAM, 0);
  initialize_sockaddr(&http_address);
  int http_port_number = bind_random_port(http_socket, &http_address);
  write_int_to_file(http_port_number, HTTP_PORT_FILENAME);
  listen(http_socket, 1);

  int accepted_server_sockets[SERVERS_NUM];
  for (int i = 0; i < SERVERS_NUM; i++) {
    accepted_server_sockets[i] = accept(server_socket, NULL, NULL);
  }

  int http_connection;
  int curr_server_ind = 0;
  while (true) {
    curr_server_ind %= SERVERS_NUM;
    http_connection = acceptHTTPClient(http_socket);

    ProcessHTTPRequest(http_connection, accepted_server_sockets[curr_server_ind], 1);

    ProcessHTTPRequest(accepted_server_sockets[curr_server_ind], http_connection, 2);

    curr_server_ind++;
  }

  return 0;
}
