#ifndef SOCKET_TOOLS_H
#define SOCKET_TOOLS_H

#include <stdbool.h>

bool ProcessHTTPRequest(int from_socket, int to_socket, int end_contdition);
#endif
