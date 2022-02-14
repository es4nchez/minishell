# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 01:48:48 by yalthaus          #+#    #+#              #
#    Updated: 2021/10/16 05:09:58 by yalthaus         ###   ########.fr        #
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

OBJS			= $(SRCS:.c=.o)

BONUS			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c
BONUS_OBJS		= $(BONUS:.c=.o)

# build
all 	: 	${NAME}

%.o 	: 	%.c
				${CC} ${CFLAGS} -c ${HEADER} $< -o ${<:.c=.o}

${NAME} : 	${OBJS}
				ar -rcs $@ $^

clean 	:
				${RM} ${OBJS} $(BONUS_OBJS)

fclean 	: 	clean
				${RM} ${NAME}

re 		: 	fclean all
bonus:		$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY 	: 	all clean fclean re bonus
