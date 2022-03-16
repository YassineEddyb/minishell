SRC = minishell.c lexer.c lexer_helpers.c parser.c parser_utils.c parse_path_and_args.c executer.c
LIBFT = libft/libft.a
GFLAGS = -Wall -Wextra -Werror
NAME = minishell

all: $(NAME)

$(NAME): $(SRC)
	cd libft && make && cd ..
	$(CC) $(SRC) $(LIBFT) -lreadline -g -o $(NAME)

clean :
	cd libft && make clean && cd ..

fclean : clean
	cd libft && make fclean && cd ..
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re