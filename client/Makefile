CC = gcc
CFLAGS = -g -Wimplicit-function-declaration
OBJS = $(shell echo $(wildcard *.c) | sed 's/\.c/\.o/g')
BIN = client

all : $(BIN)

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(CFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(BIN) 5956

clean:
	rm -rf *.o

full_clean:
	rm -rf $(BIN) *.o
