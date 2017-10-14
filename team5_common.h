#ifndef COMMON_H_
#define COMMON_H_

#define ASCII_MODE "netascii"
#define OCTET_MODE "octect"
#define MAIL_MODE "mail"

#define RRQ_OPCODE 0x0001
#define DATA_OPCODE 0x0003
#define ACK_OPCODE 0x0004
#define ERROR_OPCODE 0x0005

#define FILE_NOT_FOUND 0x0001 		//sent by server
#define ACCESS_VIOLATION 0x0002		//sent by server
#define ILLEGAL_OPERATION 0x0004	//sent by server
#define UNKNOWN_PORT_NUMBER 0x0005	//sent by server

#define RRQ_MAXBUFFLEN 150

struct RRQ_Packet
{
	unsigned short int Opcode;
	char Filename[128];
	char Mode[8];
};

struct Data_Packet
{
	unsigned short int Opcode;
	unsigned short int Block;
	char Data[512];
};

struct Ack_Packet
{
	unsigned short int Opcode;
	unsigned short int Block;
};

struct Error_Packet
{
	unsigned short int Opcode;
	unsigned short int Errorcode;
	char Errormsg[512]; 
};
#endif
