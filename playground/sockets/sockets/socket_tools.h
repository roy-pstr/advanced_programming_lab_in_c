#ifndef SOCKET_TOOLS_H
#define SOCKET_TOOLS_H

#include <netinet/in.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>

bool ProcessHTTPRequest(int from_socket, int to_socket, int end_contdition);

int acceptHTTPClient(int http_socket);

void initialize_sockaddr(struct sockaddr_in *sockaddr);

int bind_random_port(int socket, struct sockaddr_in *sockaddr);

#endif
