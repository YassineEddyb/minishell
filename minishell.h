/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/09 19:37:38 by yed-dyb          ###   ########.fr       */
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
# define DOUBLE_QUOTES '\"'
# define SINGLE_QUOTES '\''
# define SPACE ' '
# define PIPE '|'
# define GARBEGE -1
# define STDOUT 1
# define STDIN 0

typedef struct s_cmd {
	char	*path;
	char	**args;
	int		p[2];
	int		pid;
}	t_cmd;

typedef struct s_data {
	int		num_of_cmds;
	t_cmd	*cmds;
	char	*input;
	char	*output;
}	t_data;

void	parce(t_data *data, char *str, char **env);
void	execute(t_data *data, char **env);
void	ft_replace(char *s, char rm, char rp, char c);
int		look_for_paths_index(char **env);
int		get_num_of_cmds(char *str);
char	*trim_spaces (char *str);
void	fill_quotes(char *str, char c);
void	check_input_output(t_data *data ,char *str);

#endif