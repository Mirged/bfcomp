CC = gcc
CFLAGS = -o

SRCDIR = src
SOURCES = $(SRCDIR)/bfcomp.c
EXECUTABLE = bfcomp

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $@ $^

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)
