/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/06 15:09:48 by yed-dyb          ###   ########.fr       */
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
		TOKEN_PIPE,
		TOKEN_AND_AND,
		TOKEN_PIPE_PIPE,
		TOKEN_PARENTHESES,
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
	char	*input;
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
char	*parser_handle_dollar_sign(char *value, int quote);
void	parser_redirect(token_t *token, lexer_t *lexer);
void	parser_handle_word(token_t *token);
void	parser_handle_heredoc(lexer_t *lexer);
void	parser_error(char *value, int token_type);
int		is_commands_breaker(int n);
char	**dup_arr(char **arr);
int		is_empty_string(char *str);
int		is_surrounded_with_qoutes(lexer_t *lexer);
int		is_stop_charaters(char c, int quote);
int		parser_count_word(lexer_t *lexer);
char	*get_env_variable(char *var);

// minishell lib
void	free_arr(char **arr);
int		get_index(char *s, char c);
int		starts_with(char *str, char c);
void	unset_cmd(char **args);
int		get_arr_size(char **arr);
char	*join_and_free(char *s1, char *s2);
void	free_if_exists(char *str);

// executer
void	execute();
void    here_doc();
void	close_unused_pipes(int process_index);
void	close_all_pipes();
void	wait_all_child_processors();
void	check_is_path(int i);
void	ft_free_2d_table(char **table);
int		table_len(char **tab);
int		ft_strlen_till_c(char *s, char c);
char	**strdup_table(char **env);
void	dup_all(int i);
void	dup_output_file(int i);
int		is_builtin_cmd(char *cmd);

// build in commands
void 	echo_cmd(char **args);
void 	cd_cmd(char **args);
void 	pwd_cmd(void);
void 	export_cmd(char **args);
void	env_cmd(char **args);
void	exit_cmd(char **args);

// bonus functions
int handle_and_and_or(int process_index);
void parser_check_asterisk(token_t *token);

#endif