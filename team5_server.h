#ifndef SERVER_H_
#define SERVER_H_
#include "team5_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


struct client_record//This struct keeps record about a single client 
{
	int socket_descriptor;
	unsigned short int udp_port;
	vector <std::string> file_chunks;
	int total_chunks;
	int pointer;
	int last_ack_received;
	int last_frame_sent;
};

unsigned short int generate_random_port();
int minimum(int a, int b);
void upper(char* input, char* output);
bool handle_file(char* filename, vector <std::string> &v, int& total_chunks, char* mode);
void parse_string(char* filename, char* mode, char* buffer);
void send_data_packet(int sockfd, sockaddr_in client_addr, unsigned short int block, const char* data);
void send_ack_packet(int sockfd, sockaddr_in client_addr, unsigned short int block);
void send_error_packet(int sockfd, sockaddr_in client_addr, unsigned short int errorcode, char* errormsg);
void handle_new_connection(int listenfd, fd_set &allset, int &maxfd, int& client_count, char* server_ip);
void got_data(int &client_count, int descriptor, fd_set &allset, int &maxfd, int max_clients);


#endif
