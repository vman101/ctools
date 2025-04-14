SRCDIR := src
SRC := $(addprefix $(SRCDIR)/, $(addsuffix .s, asem balloc split))

OBJDIR := obj
OBJ := $(addprefix $(OBJDIR)/, $(notdir $(SRC:.s=.o)))

$(shell mkdir -p $(OBJDIR))

all: $(OBJ) 
	ld -o debug $(OBJ) -nostdlib -static

$(OBJDIR)/%.o: $(SRCDIR)/%.s
	nasm -felf64 -g $< -o $@

clean:
	rm -rf $(OBJDIR) debug
