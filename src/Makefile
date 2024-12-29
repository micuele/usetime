CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lncurses
OBJDIR = obj
SRCDIR = ../src

all: $(OBJDIR) test

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(OBJDIR)/main.o
	$(CC) $^ -o $@ $(LDFLAGS)

run: test
	./test

clean:
	rm -f test $(OBJDIR)/*.o

.PHONY: all clean run
