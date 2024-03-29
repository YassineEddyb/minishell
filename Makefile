SRC = minishell.c minishell_lib.c minishell_lib_2.c\
	lexer.c lexer_helpers.c lexer_inits.c\
	parser.c parser_utils.c parse_path_and_args.c parser_2.c parser_helpers.c parser_helpers_2.c parser_dollar_sign.c parser_bonus.c\
	executer.c executer_dup.c executer_utils.c heredoc.c executer_bnous.c

CMDS = echo_cmd.c cd_cmd.c pwd_cmd.c export_cmd.c unset_cmd.c exit_cmd.c env_cmd.c norm.c help_cmds.c

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
LIBFT = libft/libft.a
READLINE = -L /Users/yed-dyb/Desktop/cursus/brew/opt/readline/lib -I /Users/yed-dyb/Desktop/cursus/brew/opt/readline/include 
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
GREEN=\033[0;32m

all: $(NAME)

$(NAME): $(SRC) $(CMDS)
	@cd libft && make && cd ..
	@printf "${GREEN}compiling...\n"
	@$(CC) $(CFLAGS) $(SRC) $(CMDS) $(GNL) $(LIBFT) $(READLINE) -lreadline -o $(NAME)
	@stty -echoctl
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