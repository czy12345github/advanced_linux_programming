all : server client

server : server.o
	gcc -o server server.o

client : client.o
	gcc -o client client.o

clean :
	rm *.o server client
