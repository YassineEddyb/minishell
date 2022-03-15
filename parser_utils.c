/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:28:34 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/15 15:03:28 by yed-dyb          ###   ########.fr       */
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

    str = ft_strjoin(s1, lexer_get_char_as_string(sep));
    str = ft_strjoin(str, s2);

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
	arr = NULL;
}