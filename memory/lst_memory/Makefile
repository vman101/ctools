# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 15:02:31 by vvobis            #+#    #+#              #
#    Updated: 2024/12/10 21:23:05 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc

CFLAGS = -Werror -Wextra -Wall

SRC := memory.c list.c ft_free.c

OBJDIR := obj
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

LIBDIR := lib
TARGET := $(LIBDIR)/memory.a

ifdef RELEASE
CFLAGS -= -g3
endif

MKDIR = mkdir
ifeq ($(OS), Windows_NT)
RM = del /S /Q
else
RM = rm -rf
MKDIR += -p
endif

all: $(TARGET)

$(TARGET): $(OBJ) | $(LIBDIR)
	ar rcs $@ $(OBJ)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR): $(OBJDIR)
	$(MKDIR) $(LIBDIR)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(LIBDIR)

re: fclean all
