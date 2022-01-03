BDIR = bin
IDIR = include
ODIR = obj
SDIR = src

CC = gcc
CFLAGS = -g -Wall -Wextra -std=gnu11 -I$(IDIR)
LFLAGS = -lm

_PROG = client
PROG = $(patsubst %,$(BDIR)/%,$(_PROG))

_DEP = LZW.h huffman.h
DEP = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = LZW.o huffman.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: run dirs all clean delete

run: all
	./$(PROG)

all : dirs $(OBJ)
	$(CC) $(LFLAGS) $(CFLAGS) -o $(PROG) $(OBJ)

dirs:
	@mkdir -p bin
	@mkdir -p obj

$(ODIR)/%.o: $(SDIR)/%.c $(DEP)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(ODIR)
delete: clean
	rm -rf $(BDIR)
