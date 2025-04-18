SRCDIR := src
MATHDIR := $(SRCDIR)/math
STRDIR := $(SRCDIR)/string
COREDIR := $(SRCDIR)/core
PRINTDIR := $(SRCDIR)/print
FILEDIR := $(SRCDIR)/file
PARSEDIR := $(SRCDIR)/parse

# Define source files
MATHSRC := $(addprefix $(MATHDIR)/, $(addsuffix .s, \
            operators \
            ))
STRSRC := $(addprefix $(STRDIR)/, $(addsuffix .s, \
            strlen split strcpy substr is_num strcmp\
            ))
CORESRC := $(addprefix $(COREDIR)/, $(addsuffix .s, \
            malloc exit file_ops memchr syscall_err \
            ))
PRINTSRC := $(addprefix $(PRINTDIR)/, $(addsuffix .s, \
            print putnumber \
            ))
FILESRC := $(addprefix $(FILEDIR)/, $(addsuffix .s, \
            read_file \
            ))
PARSESRC := $(addprefix $(PARSEDIR)/, $(addsuffix .s, \
            parse debug_token \
            ))

# Collect all source files - now using the file variables, not directory variables
SRC := $(SRCDIR)/start.s $(MATHSRC) $(STRSRC) $(CORESRC) $(PRINTSRC) $(FILESRC) $(PARSESRC)

OBJDIR := obj
OBJ := $(patsubst %.s,$(OBJDIR)/%.o,$(notdir $(SRC)))

all: debug

debug: $(OBJDIR) $(OBJ)
	ld -o $@ $(OBJ) -nostdlib -static

# Pattern rules for object files - added the missing rules for string and print
$(OBJDIR)/%.o: $(SRCDIR)/%.s
	nasm -felf64 -F dwarf -g $< -o $@

$(OBJDIR)/%.o: $(MATHDIR)/%.s
	nasm -felf64 -F dwarf -g $< -o $@

$(OBJDIR)/%.o: $(STRDIR)/%.s
	nasm -felf64 -F dwarf -g $< -o $@

$(OBJDIR)/%.o: $(COREDIR)/%.s
	nasm -felf64 -F dwarf -g $< -o $@

$(OBJDIR)/%.o: $(PRINTDIR)/%.s
	nasm -felf64 -F dwarf -g $< -o $@

$(OBJDIR)/%.o: $(FILEDIR)/%.s
	nasm -felf64 -F dwarf -g $< -o $@

$(OBJDIR)/%.o: $(PARSEDIR)/%.s
	nasm -felf64 -F dwarf -g $< -o $@

$(OBJDIR): 
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) debug

re: clean all

.PHONY: all clean re
