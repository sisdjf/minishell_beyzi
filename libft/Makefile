# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sizitout <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 13:47:01 by hauerbac          #+#    #+#              #
#    Updated: 2024/11/06 00:26:00 by sizitout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

SRCS =  ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	get_next_line_utils.c \
	get_next_line.c \
	ft_printf.c\
	ft_putchar.c\
	ft_puthex.c\
	ft_putnbr.c\
	ft_putnbrpo.c\
	ft_putptr.c\
	ft_putstr.c\

OBJS = ${SRCS:.c=.o}

SRCS_BONUS =	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

NAME = libft.a

NAMESO = libft.so

%.o : %.c
	@cc ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@ar rc ${NAME} ${OBJS}
	@ranlib ${NAME}

all : ${NAME}

clean:
	@rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	@rm -f ${NAME}
	@rm -f ${NAMESO}
	@rm -f a.out

re: fclean all

bonus: ${OBJS_BONUS}
	ar rc ${NAME} ${OBJS_BONUS}
	ranlib ${NAME}

so:
	cc -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(SRCS_BONUS)
	gcc -nostartfiles -shared -o ${NAMESO} $(OBJS) $(OBJS_BONUS)