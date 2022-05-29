SRC = minishell.c minishell_lib.c\
	lexer.c lexer_helpers.c lexer_inits.c\
	parser.c parser_utils.c parse_path_and_args.c parser_helpers.c parser_dollar_sign.c parser_bonus.c\
	executer.c executer_utils.c heredoc.c executer_bnous.c

CMDS = echo_cmd.c cd_cmd.c pwd_cmd.c export_cmd.c unset_cmd.c exit_cmd.c env_cmd.c

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
LIBFT = libft/libft.a
READLINE = -L readline/lib -I readline/include
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
GREEN=\033[0;32m

all: $(NAME)

$(NAME): $(SRC) $(CMDS)
	@printf "${GREEN}compiling...\n"
	@cd libft && make && cd ..
	@$(CC) -g $(SRC) $(CMDS) $(GNL) $(LIBFT) -lreadline -o $(NAME)

clean :
	@printf "${GREEN}cleaning...\n"
	@cd libft && make clean && cd ..

fclean : clean
	@printf "${GREEN}cleaning...\n"
	@cd libft && make fclean && cd ..
	@rm -rf $(NAME)

test: 

re : fclean all

.PHONY: all clean fclean re