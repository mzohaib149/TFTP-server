all: server clean

server: team5_server.o
	g++ team5_server.o -o server

team5_server.o: team5_server.cc team5_server.h team5_common.h
	g++ -c team5_server.cc

clean: 
	rm *.o
