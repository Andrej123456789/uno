CC = gcc
CFLAGS = -g
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
	rm -rf uno $(BIN) *.o