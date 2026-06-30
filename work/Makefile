CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = mainOBJS = main.o server.o client.o

all: $(TARGET)



$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)