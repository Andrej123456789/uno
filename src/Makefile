CC = gcc
CFLAGS = -llua -L../lua -I../lua -lm -ldl
OBJS = $(shell echo $(wildcard *.c) | sed 's/\.c/\.o/g')
BIN = uno

all : $(BIN)

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(CFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(BIN)

clean:
	rm -rf uno $(BIN) *.o