# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 12:23:24 by yalthaus          #+#    #+#              #
#    Updated: 2022/02/04 14:35:19 by yalthaus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Exec Name
NAME	= minishell

# Compilation
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
HEADS		= -I$(INC) -I${LIBFTDIR} -I${HOME}/.brew/Cellar/readline/8.1.2/include/
LIBS		= -L${HOME}/.brew/Cellar/readline/8.1.2/lib/ -lreadline -lhistory
DEBUG_FILE	= .debug
JPP			= $(shell cat ${DEBUG_FILE} | tr -d '\n')
CDEBUG		= 

# SRC
SRCDIR 		= ./src/
INC			= ./inc/
LIBFTDIR	= ./libft/
BUILDDIR	= ./build/
LIBFT		= $(addprefix $(LIBFTDIR), libft.a)
SRCNAMES	= $(shell ls $(SRCDIR) | grep -E ".+\.c")
SRCS		= $(addprefix $(SRCDIR), $(SRCNAMES))

# command + OBJ
RM		= rm -rf
MKDIR	= mkdir -p
MAKE	= make -C
OBJS	= $(addprefix $(BUILDDIR), $(SRCNAMES:.c=.o))

# Action

all: padebug $(NAME)

padebug:
ifneq ($(JPP),0)
	@echo "0" > .debug
endif

isdebug:
ifneq ($(JPP),1)
	@echo 1 > .debug
endif

$(BUILDDIR):
			@mkdir -p $(BUILDDIR)

$(BUILDDIR)%.o:$(SRCDIR)%.c $(DEBUG_FILE)
			$(CC) $(CFLAGS) $(HEADS) -o $@ -c $<

$(LIBFT):
			$(MAKE) $(LIBFTDIR) bonus

$(NAME): $(BUILDDIR) $(LIBFT) $(OBJS) $(DEBUG_FILE)
			$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LIBS)
clean:
			rm -rf $(BUILDDIR)
			$(MAKE) $(LIBFTDIR) clean

fclean: clean
			$(MAKE) $(LIBFTDIR) fclean
			rm -f $(NAME)

debug: CFLAGS += $(CDEBUG)
debug: isdebug $(NAME)
re: fclean $(NAME)

.PHONY: all fclean clean debug re 
