/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/14 20:28:31 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>


# define OLD_THAN '>'
# define LESS_THAN '<'
# define DOUBLE_QUOTES '"'
# define SINGLE_QUOTES '\''
# define SPACE ' '
# define PIPE '|'
# define DOLLAR_SIGN '$'
# define GARBEGE -1
# define STDOUT 1
# define STDIN 0

typedef struct token_s
{
	enum {
		TOKEN_END,
		TOKEN_WORD,
		TOKEN_OLD_THAN,
		TOKEN_LESS_THAN,
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
	int		num_of_cmds;
	t_cmd	*cmds;
	int 	index;
	char	*input;
	char	*output;
}	t_data;

t_data data;

// lexer
void	lexer(char *str);
token_t *init_token(int type, char *value);
int		lexer_strlen(lexer_t *lexer, char c);
void	lexer_next_char(lexer_t *lexer);
void	lexer_skip_spaces(lexer_t *lexer);
char	*lexer_get_char_as_string(char c);
int		is_special_character(char c);
lexer_t *init_lexer(char *str);
token_t *lexer_get_next_token(lexer_t *lexer);

// parser
void	parser(char *str);
char	*join_with_sep(char *s1, char *s2, char sep);
int		get_num_of_cmds(char *str);


void	parce(t_data *data, char *str, char **env);
void	execute(t_data *data, char **env);
void	ft_replace(char *s, char rm, char rp, char c);
int		look_for_paths_index(char *var, char **env);
char	*trim_spaces (char *str);
void	fill_quotes(char *str, char c);
void	check_input_output(t_data *data ,char *str);
void	handle_quotes(t_data *data, int i, char c);
void	fill_quotes(char *str, char c);
char	*get_env_variable(char *var, char **env);
void	handle_dollar_sign(t_data *data, char **env);
int		get_index(char *s, char c);

#endif