NAME    = minishell
 
CC      = cc

CFLAGS  = -Wall -Wextra -Werror -g3 

RM      = rm -f

LIBFT          = libft

FT_LIBFT        = libft/libft.a

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	minishell.c parsing/utils.c parsing/operator.c parsing/single_greater.c \
                    parsing/double_greater.c parsing/token.c parsing/utils_token.c parsing/utils.lst.c \
                    parsing/expand.c parsing/utils_expand.c parsing/utils_env.c parsing/quotes.c parsing/free.c \
                    builtins/builtins.c builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c \
                    builtins/pwd.c builtins/unset.c builtins/utils_exit.c parsing/parse.c parsing/in_out_files.c parsing/append_heredoc.c exec/exec.c exec/free.c
OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

HEAD	=	-I.

all : ${NAME}

${NAME} : ${DIR_OBJS} ${OBJS}
		${MAKE} -C ${LIBFT}
		${CC} ${OBJS} ${HEAD} -o ${NAME} ${FT_LIBFT} -lreadline
		# @echo "\033[31;5mminishell\033[0m"

${OBJS} : ${DIR_OBJS}/%.o : ${DIR_SRCS}/%.c
	${CC} ${CFLAGS} ${HEAD} -c $< -o $@

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/parsing
	mkdir -p objs/builtins
	mkdir -p objs/exec
	mkdir -p objs/builtins


leaks : all
	valgrind --leak-check=full --track-fds=yes --suppressions=ignore.txt ./minishell

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
