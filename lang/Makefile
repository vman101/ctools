SRC := asem.s


OBJDIR := obj
OBJ := $(OBJDIR)/$(SRC:.s=.o)

all: 
	nasm -felf64 -g $(SRC) -o $(OBJ)
	ld -o debug $(OBJ) -nostdlib -static
