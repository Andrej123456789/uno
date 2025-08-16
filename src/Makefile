CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g
LDFLAGS = -lm -ljson-c

OBJDIR = objects
OBJS = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(wildcard *.c)))
OBJS += $(addprefix $(OBJDIR)/, $(patsubst server/%.c, %.o, server/server_posix.c))

BINFOLDER = executable
BIN = $(BINFOLDER)/uno_pp

all : $(OBJDIR) $(BINFOLDER) $(BIN)

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINFOLDER):
	mkdir $(BINFOLDER)

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(LDFLAGS)

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o : server/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	@./$(BIN) settings/default.json

clean:
	rm -rf $(OBJDIR) $(BINFOLDER)
