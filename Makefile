# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lybey <lybey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 00:22:13 by lybey             #+#    #+#              #
#    Updated: 2024/10/17 00:22:29 by lybey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell
 
CC      = cc

CFLAGS = -Wall -Wextra -Werror -g3

LDFLAGS = -lreadline

SRCS = minishell.c utils.c operator.c single_greater.c double_greater.c token.c utils_token.c utils.lst.c expand.c utils_expand.c utils_env.c

OBJS = ${SRCS:.c=.o}

INCLUDES = -I. -I/usr/include -Ilibft

LIBFT = libft/libft.a

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	make -C libft

%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f ${OBJS}
	make -C libft clean

fclean:		clean
	rm -f ${NAME}
	make -C libft fclean

re:			fclean all

leaks : all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=ignore.txt ./minishell

clean :
	${RM} ${OBJS} 
	make clean -C libft

fclean : clean
	${RM} ${NAME} 
	make fclean -C libft
	${RM} ${FT_LIBFT}

re : fclean all

-include $(DEPS)

.PHONY : all clean fclean re
