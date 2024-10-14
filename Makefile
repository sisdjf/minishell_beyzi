NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -lreadline

SRCS = env.c minishell.c utils.c operator.c single_greater.c double_greater.c token.c utils.lst.c expand.c utils_expand.c utils_env.c echoo.c pwd.c builtins.c cd.c unset.c export.c exit.c utils_exit.c

OBJS = ${SRCS:.c=.o}

INCLUDES = -I. -I/usr/include -Ilibft

LIBFT = libft/libft.a

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	make -C libft

%.o: %.c include/minishell.h
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