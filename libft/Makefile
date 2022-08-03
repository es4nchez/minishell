# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 01:48:48 by yalthaus          #+#    #+#              #
#    Updated: 2022/07/22 15:09:52 by yalthaus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#Name of archive
NAME 	= libft.a

#compiler option
CC 		= gcc
CFLAGS 	= -Wall -Werror -Wextra

RM 		= rm -f

#header path
HEADER 	= -I includes



SRCS			=	ft_isalpha.c\
					ft_memcmp.c\
					ft_strchr.c\
					ft_strrchr.c\
					ft_atoi.c\
					ft_isascii.c\
					ft_strdup.c\
					ft_tolower.c\
					ft_bzero.c\
					ft_isdigit.c\
					ft_memcpy.c\
					ft_strlcpy.c\
					ft_toupper.c\
					ft_calloc.c\
					ft_isprint.c\
					ft_memmove.c\
					ft_strlen.c\
					ft_isalnum.c\
					ft_memset.c\
					ft_strncmp.c\
					ft_memchr.c\
					ft_strlcat.c\
					ft_strnstr.c\
					ft_putchar_fd.c\
					ft_putstr_fd.c\
					ft_putnbr_fd.c\
					ft_putendl_fd.c\
					ft_strjoin.c\
					ft_strtrim.c\
					ft_substr.c\
					ft_split.c\
					ft_itoa.c\
					ft_strmapi.c\
					ft_striteri.c\
					ft_realloc.c\
					ft_isinset.c\
					skip_space.c\

OBJS			= $(SRCS:.c=.o)

BONUS			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c
BONUS_OBJS		= $(BONUS:.c=.o)


# Color
_COLOR		= \033[32m
_BOLDCOLOR	= \033[32;1m
_RESET		= \033[0m
_CLEAR		= \033[0K\r\c
_OK			= [\033[32mOK\033[0m]

# build
all 	: 	${NAME}

%.o 	: 	%.c
				@echo "[..] $(NAME)... compiling $*.c\r\c"
				@${CC} ${CFLAGS} -c ${HEADER} $< -o ${<:.c=.o}
				@echo "$(_CLEAR)"

${NAME} : 	${OBJS}
				@ar -rcs $@ $^

clean 	:
				@${RM} ${OBJS} $(BONUS_OBJS)

fclean 	: 	clean
				@${RM} ${NAME}

re 		: 	fclean all
bonus:		$(OBJS) $(BONUS_OBJS)
				@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
				@echo "$(_OK) $(NAME) compiled"

.PHONY 	: 	all clean fclean re bonus
