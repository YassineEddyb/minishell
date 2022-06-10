/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/10 22:23:57 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_token
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
	}	e_type;
	char	*value;
}	t_token;

typedef struct s_lexer
{
	char	*content;
	char	c;
	int		index;
}	t_lexer;

typedef struct s_cmd {
	char	*str;
	char	*path;
	char	*output;
	char	*input;
	char	**args;
	int		heredoc;
	int		doc[2];
	int		pipe;
	int		and;
	int		or;
	int		p[2];
	int		pid;
	int		err;
}	t_cmd;

typedef struct s_data {
	char	**env;
	int		num_of_cmds;
	t_cmd	*cmds;
	int		index;
	char	*limit;
	int		append;
	int		err;
	int		exit_code;
}	t_data;

t_data	g_data;

// lexer
void	lexer(char *str);
t_token	init_token(int type, char *value);
int		lexer_strlen(t_lexer *lexer, char c);
void	lexer_next_char(t_lexer *lexer);
void	lexer_skip_spaces(t_lexer *lexer);
char	*lexer_get_char_as_string(char c);
int		is_special_character(char c);
t_lexer	*init_lexer(char *str);
t_token	lexer_get_next_token(t_lexer *lexer);
int		lexer_count_word(t_lexer *lexer);

// parser
void	parser(char *str);
void	parser_parse(t_token *token, t_lexer *lexer);
char	*join_with_sep(char *s1, char *s2, char sep);
int		get_num_of_cmds(char *str);
void	get_path_and_args(void);
void	clean_data(void);
t_token	parser_expect(t_lexer *lexer, int t_tokenype);
char	*parser_handle_dollar_sign(char *value);
void	parser_redirect(t_token *token, t_lexer *lexer);
void	parser_handle_word(t_token *token);
void	parser_handle_heredoc(t_lexer *lexer);
void	parser_error(char *value, int t_tokenype);
int		is_commands_breaker(int n);
char	**dup_arr(char **arr);
int		is_empty_string(char *str);
int		is_surrounded_with_qoutes(t_lexer *lexer);
int		is_stop_charaters(char c);
int		parser_count_word(t_lexer *lexer);
char	*get_env_variable(char *var);
void	parse_outfile(t_lexer *lexer, int append);

// minishell lib
void	free_arr(char **arr);
int		get_index(char *s, char c);
int		starts_with(char *str, char c);
int		get_arr_size(char **arr);
char	*join_and_free(char *s1, char *s2);
void	free_if_exists(char *str);
void	open_file(char *path);

// executer
void	execute(void);
void	here_doc(void);
void	close_unused_pipes(int process_index);
void	close_all_pipes(void);
void	wait_all_child_processors(void);
void	check_is_path(int i);
void	ft_free_2d_table(char **table);
int		table_len(char **tab);
int		ft_strlen_till_c(char *s, char c);
char	**strdup_table(char **env);
void	dup_all(int i);
void	dup_output_file(int i);
int		is_builtin_cmd(char *cmd);
int		ft_check_alnum(char *str);
int		ft_check_alnum2(char *str);
void	exec_cmd(int i);
char	**norm1(char **args);
char	**norm2(char **args, char **tmp);

// build in commands
void	echo_cmd(char **args);
void	cd_cmd(char **args);
void	pwd_cmd(void);
void	export_cmd(char **args);
void	env_cmd(char **args);
void	exit_cmd(char **args);
void	unset_cmd(char **args, int q);

// bonus functions
int		handle_and_and_or(int process_index);
void	parser_check_asterisk(t_token *token);

#endif