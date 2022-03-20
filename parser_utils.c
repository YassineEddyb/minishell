/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:28:34 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/19 18:41:23 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int get_index(char *s, char c)
{
	int i;

	i = 0;
	while(s[i] && s[i] != c)
		i++;
	
	return (i);
}

char *join_with_sep(char *s1, char *s2, char sep)
{
	char *str;
	char *tmp;
	char *sep_str;

	sep_str = lexer_get_char_as_string(sep);
    tmp = ft_strjoin(s1, sep_str);
	free(sep_str);
	free(s1);
    str = ft_strjoin(tmp, s2);
	free(tmp);

	return (str);
}

int get_num_of_cmds(char *str)
{
	int i;
	int len;

	i = 0;
	len = 1;
	while(str[i])
	{
		if (str[i] == PIPE)
			len++;
		i++;
	}
	return len;
}

void free_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void clean_data()
{
	int i = 0;

	while(i < data.num_of_cmds)
	{
		free(data.cmds[i].str); 
		free(data.cmds[i].path);
		free_arr(data.cmds[i].args);
		if (data.input)
			free(data.input);
		if (data.output)
			free(data.output);
		data.input = NULL;
		data.output = NULL;
		data.append = 0;
		data.heredoc = 0;
		data.err = 0;
		i++;
	}
}

int starts_with(char *str, char c)
{
	if (!str)
		return (1);
	if (str[0] == c)
		return (1);
	else
		return (0);
}