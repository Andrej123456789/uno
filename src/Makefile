CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g
LDFLAGS = -lm -ljson-c

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
	$(CC) $(OBJS) -o $(BIN) $(LDFLAGS)

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	@./$(BIN) settings/default.json

clean:
	rm -rf $(OBJDIR) $(BINFOLDER)
