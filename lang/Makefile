SRCDIR := src
SRC := $(addprefix $(SRCDIR)/, $(addsuffix .s, start malloc split exit file_ops \
	   print strlen putnumber strcpy substr memchr))

OBJDIR := obj
OBJ := $(addprefix $(OBJDIR)/, $(notdir $(SRC:.s=.o)))

$(shell mkdir -p $(OBJDIR))

all: $(OBJ) 
	ld -o debug $(OBJ) -nostdlib -static

$(OBJDIR)/%.o: $(SRCDIR)/%.s
	nasm -felf64 -F dwarf -g $< -o $@

clean:
	rm -rf $(OBJDIR) debug

re: clean all
