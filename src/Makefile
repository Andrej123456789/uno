CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g -ljson-c
OBJS = $(shell echo $(wildcard *.c) | sed 's/\.c/\.o/g')
BIN = uno

all : $(BIN) 

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(CFLAGS)

server.o : server.c
	$(CC) -c $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(BIN) default.txt

clean:
	rm -rf *.o

full_clean:
	rm -rf $(BIN) *.o
