CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g -lm -ljson-c

OBJDIR = objects
OBJS = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(wildcard *.c)))

BINFOLDER = executable
BIN = $(BINFOLDER)/uno

all : $(OBJDIR) $(BINFOLDER) $(BIN)

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINFOLDER):
	mkdir $(BINFOLDER)

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(CFLAGS)

$(OBJDIR)/server.o : server.c
	$(CC) -c $< -o $@

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	@./$(BIN) settings/default.json

clean:
	rm -rf $(wildcard *.o) objects

full_clean:
	rm -rf $(BIN) executable $(wildcard *.o) objects
