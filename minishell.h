/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/19 18:43:10 by yed-dyb          ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
// # include "Memd/mem.h"


# define OLD_THAN '>'
# define LESS_THAN '<'
# define DOUBLE_QUOTES '"'
# define SINGLE_QUOTES '\''
# define SPACE ' '
# define PIPE '|'
# define DOLLAR_SIGN '$'
# define QUESTION_MARK '?'
# define GARBEGE -1
# define STDOUT 1
# define STDIN 0
# define STDERR 2
# define ERROR 2
# define SUCCESS 0
# define FAILURE 1

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
		TOKEN_DOLLAR_SIGN,
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
	char	**args;
	int		p[2];
	int		pid;
}	t_cmd;

typedef struct s_data {
	char	**env;
	int		num_of_cmds;
	t_cmd	*cmds;
	int 	index;
	char	*input;
	char	*output;
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

// parser
void	parser(char *str);
void	parser_parse(token_t *token, lexer_t *lexer);
char	*join_with_sep(char *s1, char *s2, char sep);
int		get_num_of_cmds(char *str);
int		get_index(char *s, char c);
void	get_path_and_args();
void	free_arr(char **arr);
void	clean_data();
int		starts_with(char *str, char c);


// executer
void	execute();
void    here_doc();
void	close_unused_pipes(int process_index);
void	close_all_pipes();
void	wait_all_child_processors();
void	check_path(int i);

#endif