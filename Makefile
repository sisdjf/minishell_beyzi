NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -lreadline

SRCS = minishell.c utils.c operator.c single_greater.c double_greater.c token.c utils.lst.c expand.c

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

.PHONY:		all clean fclean re