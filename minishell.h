/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/25 17:56:02 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

# define OLD_THAN '>'
# define LESS_THAN '<'
# define DOUBLE_QUOTES '"'
# define SINGLE_QUOTES '\''
# define SPACE ' '
# define PIPE '|'
# define DOLLAR_SIGN '$'
# define AND '&'
# define QUESTION_MARK '?'
# define ASTERISK '*'
# define LEFT_PARENTHESES '('
# define RIGHT_PARENTHESES ')'
# define NEW_LINE '\n'
# define GARBEGE -1
# define STDOUT 1
# define STDIN 0
# define STDERR 2
# define ERROR 1
# define SUCCESS 0
# define FAILURE 2

typedef struct token_s
{
	enum {
		TOKEN_END,
		TOKEN_WORD,
		TOKEN_OLD_THAN,
		TOKEN_LESS_THAN,
		TOKEN_LESS_LESS,
		TOKEN_GREAT_GREAT,
		TOKEN_STRING_DOUBLE_QUOTES,
		TOKEN_STRING_SINGLE_QUOTES,
		TOKEN_PIPE,
		TOKEN_AND_AND,
		TOKEN_PIPE_PIPE,
		TOKEN_PARENTHESES,
		TOKEN_NEW_LINE
	} type;
	char *value;
} token_t;

typedef struct lexer_s
{
	char *content;
	char c;
	int index;
}	lexer_t;

typedef struct s_cmd {
	char	*str;
	char	*path;
	char	*output;
	char	**args;
	int		pipe;
	int		and;
	int 	or;
	int		p[2];
	int		pid;
}	t_cmd;

typedef struct s_data {
	char	**env;
	int		num_of_cmds;
	t_cmd	*cmds;
	int 	index;
	char	*input;
	char	*limit;
	int 	heredoc;
	int		append;
	int		err;
	int		exit_code;
}	t_data;

t_data data;

// lexer
void	lexer(char *str);
token_t init_token(int type, char *value);
int		lexer_strlen(lexer_t *lexer, char c);
void	lexer_next_char(lexer_t *lexer);
void	lexer_skip_spaces(lexer_t *lexer);
char	*lexer_get_char_as_string(char c);
int		is_special_character(char c);
lexer_t *init_lexer(char *str);
token_t lexer_get_next_token(lexer_t *lexer);
int		lexer_count_word(lexer_t *lexer);

// parser
void	parser(char *str);
void	parser_parse(token_t *token, lexer_t *lexer);
char	*join_with_sep(char *s1, char *s2, char sep);
int		get_num_of_cmds(char *str);
void	get_path_and_args();
void	clean_data();
token_t	parser_expect(lexer_t *lexer, int token_type);
char	*parser_handle_string(char *value);
void	parser_parse_2(token_t *token, lexer_t *lexer);
void	parser_handle_word(token_t *token);
void	parser_handle_append_redirect(lexer_t *lexer);
void	parser_error(char *value);
int		parser_expect_new_line(int n);
char	**dup_arr(char **arr);

// minishell lib
void	free_arr(char **arr);
int		get_index(char *s, char c);
int		starts_with(char *str, char c);
void	unset_cmd(char **args);
int		get_arr_size(char **arr);

// executer
void	execute();
void    here_doc();
void	close_unused_pipes(int process_index);
void	close_all_pipes();
void	wait_all_child_processors();
void	check_is_path(int i);

// build in commands
void echo_cmd(char **args);
void cd_cmd(char **args);
void pwd_cmd(void);
void export_cmd(char **args);

// bonus functions
int handle_and_and_or(int process_index);
void parser_check_asterisk(token_t *token);

#endif