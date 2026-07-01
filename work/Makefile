CC = gcc
CFLAGS = -Wall -Wextra -g


all: server client

server: main_server.o server.o 
	$(CC) -o server main_server.o server.o 

client: main_client.o client.o 
	$(CC) -o client main_client.o client.o 



%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f server client