SRC = minishell.c parcer.c executer.c parcer_helpers.c simplify_command.c parce_redirecting.c
LIBFT = libft/libft.a
GFLAGS = -Wall -Wextra -Werror
NAME = minishell

all: $(NAME)

$(NAME): $(SRC)
	cd libft && make && cd ..
	$(CC) $(GFLAGS) $(SRC) $(LIBFT) -lreadline -o $(NAME) -fsanitize=address

clean :
	cd libft && make clean && cd ..

fclean : clean
	cd libft && make fclean && cd ..
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re