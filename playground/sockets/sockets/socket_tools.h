#ifndef SOCKET_TOOLS_H
#define SOCKET_TOOLS_H


#include <stdbool.h>

bool ProcessHTTPRequest(int client_socket, int server_socket, int end_of_msg_condition);
bool ProcessAnswer(int from_socket, int to_socket, bool send_to);
#endif // SOCKET_SEND_RECV_TOOLS_H


