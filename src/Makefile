CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g
OBJS = $(shell echo $(wildcard *.c) | sed 's/\.c/\.o/g')
BIN = uno

all : $(BIN)

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(CFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(BIN) default.txt

clean:
	rm -rf *.o

full_clean:
	rm -rf $(BIN) *.o
