#include "team5_common.h"
#include "team5_server.h"

vector<client_record> client_list;

unsigned short int generate_random_port()//generates random port between 1024 and 65535
{
	unsigned short int value;
	value = (rand()%64512) + 1024;	
}

int minimum(int a, int b)
{
	if (a<b)
		return a;
	else 
		return b;
}

void upper(char* input, char* output)
{
	for (int i=0;i<strlen(input);i++)
	{
		output[i] = toupper(input[i]);
	}
	output[strlen(input)]='\0';
}

bool handle_file(char* filename, vector <std::string> &v, int& total_chunks, char* mode)//reads 511 chunks from file ad appends \0 at the end. If there are exactly 511 bytes in last chunk, it creates new chunk with 0 data bytes
{
	
	int count = 0;
	char uppercase_mode[12];
	//std::io_base::openmode openingmode;
	upper(mode, uppercase_mode);
	fstream(myfile);	
	if (!strcmp(uppercase_mode, "NETASCII"))
	{
		myfile.open(filename,ios::in);
		
	}
	else if (!strcmp(uppercase_mode, "OCTET"))
	{
		myfile.open(filename,ios::in|ios::binary);
		
	}
	//fstream myfile(filename,openingmode);	
	if (!myfile.is_open())
	{
		cout<<"can't open file"<<endl;
		return false;
	}
	else
	{
		streampos begin, end, size;
		cout<<"Successfully opened file with "<<uppercase_mode<<" mode!"<<endl;
		begin=myfile.tellg();
		myfile.seekg(0, ios::end);
		end = myfile.tellg();
		size = end - begin;
		cout<<"File size "<<size<<endl;	
		myfile.seekg(0, ios::beg);
		bool flag = false;
		while (!flag)
		{	
			streampos min = minimum((end-(myfile.tellg())),512);
			int minint = (int)min;
			char buffer[minint+1];			
			if (min < 512)
			{
				flag = true;
			}
			if (min == 0)
			{
				strcpy(buffer,"");
				v.push_back(buffer);
			}	
			else
			{
				myfile.read(buffer,min);
				
				buffer[min] ='\0';
				v.push_back(buffer);
			}		
			count++;
		}
		
		total_chunks=count;
		myfile.close();
		return true;
	}
}

void parse_string(char* filename, char* mode, char* buffer)//takes the string containing filename and mode and parses it to produce filename and mode spearately
{
	
	int count1 = 0;
	int count = 2;
	while (buffer[count]!=0x00)
	{
		filename[count1] = buffer[count];
		count++;
		count1++;
	}
	
	filename[count1] = '\0';
	
	count++;
	count1=0;
	while (buffer[count]!=0x00)
	{
		mode[count1] = buffer[count];
		count++;
		count1++;
	}
	
	mode[count1] = '\0';
	
}


void send_data_packet(int sockfd, sockaddr_in client_addr, unsigned short int block, const char* data)
{
	struct Data_Packet dp;
	dp.Opcode = htons(DATA_OPCODE);
	dp.Block = htons(block);
	strcpy(dp.Data,data);

	
	int buffer_size = 0;	
	buffer_size = strlen(data) + 4;
	char buffer[buffer_size];
	memset(buffer, 0, buffer_size);
	memcpy(&buffer[0], &dp.Opcode, 2);
	memcpy(&buffer[2], &dp.Block, 2);
	memcpy(&buffer[4], dp.Data, strlen(dp.Data));
	socklen_t addr_len = sizeof(client_addr);
	int bytes_sent = sendto(sockfd, buffer, buffer_size, 0, (struct sockaddr* )&client_addr, addr_len);
	cout<<"sent "<<bytes_sent<<" bytes of data packet with block# "<<block<<endl; 	
	
}

void send_ack_packet(int sockfd, sockaddr_in client_addr, unsigned short int block)
{
	struct Ack_Packet ap;
	ap.Opcode = htons(ACK_OPCODE);
	ap.Block = htons(block);
	
	
	int buffer_size = 4;	
	char buffer[buffer_size];
	memset(buffer, 0, buffer_size);
	memcpy(&buffer[0], &ap.Opcode, 2);
	memcpy(&buffer[2], &ap.Block, 2);
	
	socklen_t addr_len = sizeof(client_addr);
	int bytes_sent = sendto(sockfd, buffer, buffer_size, 0, (struct sockaddr* )&client_addr, addr_len);
	
	cout<<"sent "<<bytes_sent<<" bytes of ack packet"<<endl; 	
		
	
}

void send_error_packet(int sockfd, sockaddr_in client_addr, unsigned short int errorcode, char* errormsg)
{
	struct Error_Packet ep;
	ep.Opcode = htons(ERROR_OPCODE);
	ep.Errorcode = htons(errorcode);
	strcpy(ep.Errormsg,errormsg);

	
	int buffer_size = 0;	
	buffer_size = strlen(errormsg) + 1 + 4;
	char buffer[buffer_size];
	memset(buffer, 0, buffer_size);
	memcpy(&buffer[0], &ep.Opcode, 2);
	memcpy(&buffer[2], &ep.Errorcode, 2);
	memcpy(&buffer[4], ep.Errormsg, strlen(ep.Errormsg));
	int i = strlen(ep.Errormsg) + 4;
	char var = 0x00;
	memcpy(&buffer[i], &var, 1);
	socklen_t addr_len = sizeof(client_addr);
	int bytes_sent = sendto(sockfd, buffer, buffer_size, 0, (struct sockaddr* )&client_addr, addr_len);

	cout<<"sent "<<bytes_sent<<" bytes of error packet with error code "<<errorcode<<endl; 	
		
}


void handle_new_connection(int listenfd, fd_set &allset, int &maxfd, int& client_count, char* server_ip)
{
	//receive new read request
	//if it is not read request
		//send  error message
		
		
	//else
		//if file exists
			//read file and create chunks
			//create new socket and put it in appropriate record of client
			//send the first chunk on this new socket
		//if file doesn't exist
			//send error message
			
	   	
	cout<<"got a new connection"<<endl;
	sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	char opcode_buffer[2];
	int nbytes = recvfrom(listenfd, opcode_buffer, 2, 0 ,(struct sockaddr* )&client_addr, &addr_len);
	cout<<"received "<<nbytes<<" bytes of opcode"<<endl;
	int newsock;
	srand(time(NULL));
	unsigned short int new_server_port = generate_random_port();
	cout<<"created a new socket on random port "<<new_server_port<<endl;
	struct sockaddr_in servaddr;	
	
	if ((newsock = socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		perror("socket error");
		exit(0);
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET,server_ip,&(servaddr.sin_addr));
	servaddr.sin_port=htons(new_server_port);
	
	if ((bind(newsock, (struct sockaddr *) &servaddr, sizeof(servaddr)))<0)
	{
		perror("bind error");
		exit(0);
	}
	
	if (nbytes == 2)
	{
		unsigned short int opcode;
		memcpy(&opcode, &opcode_buffer[0], 2);
		opcode = ntohs(opcode);
		if (opcode == RRQ_OPCODE)
		{
			char filename[128];
			char mode[16];
			char buffer[150];
			client_count++;
			int nbytes2 = recvfrom(listenfd, buffer, RRQ_MAXBUFFLEN, 0 ,(struct sockaddr* )&client_addr, &addr_len);
			cout<<"received "<<nbytes2<<" of remaining RRQ packet"<<endl;
			
			parse_string(filename, mode, buffer);
			//cout<<mode<<endl;
			bool is_file_read;
			int total_chunks = 0;

			struct client_record cr;
			cr.socket_descriptor = newsock; 
			cr.udp_port = ntohs(client_addr.sin_port);
		  	cr.pointer = 0;
			
			is_file_read = handle_file(filename, cr.file_chunks, cr.total_chunks, mode);
			
			
			if (!is_file_read)
			{
				char buf[50];
				strcpy(buf,"file not found"); 	
				send_error_packet(newsock, client_addr, FILE_NOT_FOUND,buf);
			}
			else if(is_file_read)
			{
				cr.last_frame_sent = 1;
				cr.last_ack_received = 0;
				client_list.push_back(cr);
				const char* buff;
				buff = (cr.file_chunks[0]).c_str();
				
				send_data_packet(newsock, client_addr, 1 , buff);
				cout<<"*********************************"<<endl;
				cout<<"last frame sent "<<client_list[0].last_frame_sent<<endl;
				
				cout<<"*********************************"<<endl;
				FD_SET(newsock, &allset);
				if (newsock>maxfd)
				{
				maxfd = newsock;
				}
			}			
		}
		else
		{
			char buf[50];
			strcpy(buf, "illegal operation");
			send_error_packet(newsock, client_addr, ILLEGAL_OPERATION, buf);
		}
	}
	
	
	
	
}

void got_data(int &client_count, int descriptor, fd_set &allset, int &maxfd, int max_clients)
{
	//received something from already existing client
	
	//it can be either ack or error packet
	//first receive first two bytes to determine packet type
	//if received bytes are zero, close the connection, remove descriptor from fdset
	//if it is ack packet
		//receiver further 2 bytes of ack#
		//extract client information from client_list
		//send the next sequence numbered packet from the appropriate record (based on ack)
		//*note: ack will contain the squence number of packet being acknowledged, not the next number
	//if it is error packet
		//close the descriptor, remove descriptor from fdset
	sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	char opcode_buffer[2];
	memset(opcode_buffer, 0, 2);
	int nbytes = recvfrom(descriptor, opcode_buffer, 2, 0 ,(struct sockaddr* )&client_addr, &addr_len);

	cout<<"received "<<nbytes<<" bytes of opcode"<<endl;
	if (nbytes == 0)
	{
		close(descriptor);
		FD_CLR(descriptor, &allset);
		client_count--;
	}
	else
	{
		unsigned short int opcode;
		memcpy(&opcode, &opcode_buffer[0], 2);
		opcode = ntohs(opcode);
		if (opcode == ACK_OPCODE)
		{
			char block_buffer[2];
			unsigned short int block=0;
			memset(block_buffer, 0, 2);
			int nbytes1 = recvfrom(descriptor, block_buffer, 2, 0 ,(struct sockaddr* )&client_addr, &addr_len);
			//cout<<"||||||Block_buffer|||||  "<<sizeof(block_buffer)<<endl;
			cout<<"received an ACK"<<endl;
			memcpy(&block, &block_buffer[0], 2);
			block = ntohs(block);
			struct Ack_Packet ap;
			ap.Opcode = opcode;
			ap.Block = block;
			//cout<<"received "<<nbytes1<<" bytes of block# "<<block<<endl;
			
			for (int i=0; i<client_count; i++)
			{
				if (client_list[i].socket_descriptor == descriptor)
				{
					//if last ack received != block
					//send the next frame
					//increment last frame sent
					//if (client_list[i].last_ack_received != ap.Block)
					{
						
						client_list[i].last_frame_sent++;
						client_list[i].last_ack_received++;
						client_list[i].pointer++;
						int x = client_list[i].pointer;
						const char* buff;	
						buff = client_list[i].file_chunks[x].c_str();
						send_data_packet(descriptor, client_addr, client_list[i].last_frame_sent , buff);

					      	cout<<"*********************************"<<endl;
						cout<<"last frame sent "<<client_list[i].last_frame_sent<<" for client with port "<<client_list[i].udp_port<<endl;
						cout<<"last last ack received "<<client_list[i].last_ack_received<<" for client with port "<<client_list[i].udp_port<<endl;
						cout<<"*********************************"<<endl;
						if (client_list[i].last_frame_sent == client_list[i].total_chunks)
						{

							cout<<"finished sending file"<<" for client with port "<<client_list[i].udp_port<<endl;
							//sleep(2000);
							for (int count=0; count<client_list.size(); count++)
							{
								if (client_list[count].socket_descriptor == descriptor)
								{
									client_list.erase(client_list.begin()+count);
									break;
								}
							}
							close(descriptor);
							FD_CLR(descriptor, &allset);	
							client_count--;
							
								
						}
						break;
					}
					
				}
			}	
			
		}
		else if (opcode == ERROR_OPCODE)
		{
			close(descriptor);
			FD_CLR(descriptor, &allset);
			client_count--;
		}
		
	}

}

int main(int argc,char** argv)
{
	int client_count = 0;
	if (argc!=4)
	{
		cout<<"Please enter 3 arguments"<<endl;
		cout<<"quitting ..."<<endl;		
		return 0;
	}
	char server_ip[50];
	char max_clients_string[50];
	char server_port_string[50];
	int max_clients;
	unsigned short int port;	
	strcpy(server_ip,argv[1]);
	strcpy(server_port_string,argv[2]);
	strcpy(max_clients_string,argv[3]);
	max_clients = atoi(max_clients_string);
	port = atoi(server_port_string);
	cout<<server_ip<<" "<<port<<endl;
	int listenfd;
	struct sockaddr_in servaddr;	
	
	if ((listenfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		perror("socket error");
		return 0;
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET,server_ip,&(servaddr.sin_addr));
	servaddr.sin_port=htons(port);
	
	if ((bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)))<0)
	{
		perror("bind error");
		return 0;
	}


	int maxfd = listenfd;
	fd_set allset, rset;
	FD_ZERO(&allset);
	FD_ZERO(&rset);
	FD_SET(listenfd, &allset);

	for (;;)
	{
		rset = allset;
		int nready = select(maxfd+1, &rset, NULL, NULL, NULL);
		for (int i=0; i<=maxfd; i++) // we check all the socket descriptors for data
		{
			if (FD_ISSET(i,&rset))//if there is a descriptor with data
			{
				if (i==listenfd)//we got a new connection
				{
					handle_new_connection(listenfd, allset,maxfd,client_count,server_ip);

				}
				else// we got data from an existing connection
					got_data(client_count, i, allset, maxfd, max_clients);
				
			}
		}
		
	}

	return 0;
}


