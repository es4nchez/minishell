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
CFLAGS		= -Wall -Wextra -Werror
DEBUG_FILE	= .debug
JPP			= $(shell cat ${DEBUG_FILE} | tr -d '\n')
CDEBUG		= -fsanitize=address -g

# SRC
SRC_FOLDER 		= src/
LIBFT_FOLDER	= $(addprefix $(SRC_FOLDER), libft/)
LIBFT_ARC		= $(addprefix $(LIBFT_FOLDER), libft.a)
SRC_FILES		= minishell.c\
				  dir_name.c\
				  env_function.c\
				  execve_threading.c\
				  input.c\
				  handle_ctrl.c\
				  handle_input.c
SRCS			= $(addprefix $(SRC_FOLDER), $(SRC_FILES))

# command + OBJ
RM		= rm -rf
MKDIR	= mkdir -p
MAKE	= make -C
OBJS	= $(SRCS:%.c=%.o)

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

libft:
			$(MAKE) $(LIBFT_FOLDER)

$(NAME): $(OBJS) $(DEBUG_FILE) | libft
			$(CC) -lreadline -I $(LIBFT_FOLDER) -I $(SRC_FOLDER) $(CFLAGS) $(OBJS) $(LIBFT_ARC) -o $@
clean:
			rm -f $(OBJS)
			$(MAKE) $(LIBFT_FOLDER) clean

fclean: clean
			$(MAKE) $(LIBFT_FOLDER) fclean
			rm -f $(NAME)

debug: CFLAGS += $(CDEBUG)
debug: isdebug $(NAME)
re: fclean $(NAME)

.PHONY: all fclean clean debug re 
