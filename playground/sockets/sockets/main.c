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

#define DEBUG

typedef int SOCKET;

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
    printf("Doron: rand_port_num = %d\n", rand_port_num);
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
#ifdef DEBUG
  printf("Waiting for incoming connection (client) ...\n");
#endif

  int accepted_http_socket = accept(http_socket, NULL, NULL);
#ifdef DEBUG
  printf("HTTP connection accepted\n");
#endif
  return accepted_http_socket;
}

int main()
{
  srand(time(NULL));

  struct sockaddr_in server_address;
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);  // Doron: int->SOCKET?
  initialize_sockaddr(&server_address);
  int server_port_number = bind_random_port(server_socket, &server_address);
  write_port_to_file(server_port_number, SERVER_PORT_FILENAME);
  listen(server_socket, COMPUTER_NUM);

  struct sockaddr_in http_address;
  int http_socket = socket(AF_INET, SOCK_STREAM, 0);  // Doron: int->SOCKET?
  initialize_sockaddr(&http_address);
  int http_port_number = bind_random_port(http_socket, &http_address);
  write_port_to_file(http_port_number, HTTP_PORT_FILENAME);
  listen(http_socket, 1);

  int accepted_server_sockets[COMPUTER_NUM];
  for (int i = 0; i < COMPUTER_NUM; i++) {
#ifdef DEBUG
    printf("Waiting for incoming connection (server) ...\n");
#endif
    accepted_server_sockets[i] = accept(server_socket, NULL, NULL);
#ifdef DEBUG
    printf("Server connection #%d accepted\n", i + 1);
#endif
  }

  int http_connection;
  int curr_server_ind = 0;
  while (true) {
    curr_server_ind %= COMPUTER_NUM;

#ifdef DEBUG
    printf("Doron: curr_server_ind = %d\n", curr_server_ind);
#endif
    /* wait for: connection with client (web browser): */
    http_connection = acceptHTTPClient(http_socket);

    /* wait for: Client -> LB; then: LB -> server.py */
#ifdef DEBUG
    printf("wait for: Client -> LB; then: LB -> server.py\n");
#endif
    // ProcessHTTPRequest(http_connection,http_connection , 1);
    ProcessHTTPRequest(http_connection, accepted_server_sockets[curr_server_ind], 1);

    /* wait for: server.py -> LB then: LB->Client*/
#ifdef DEBUG
    printf("wait for: server.py -> LB then: LB->Client\n");
#endif
    ProcessHTTPRequest(accepted_server_sockets[curr_server_ind], http_connection, 2);

    /* next */
    curr_server_ind++;
  }

  return 0;
}
