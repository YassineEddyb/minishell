/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:28:39 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/09 17:17:20 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int is_redirect_characher(char c)
{
	if (c == OLD_THAN || c == LESS_THAN)
		return 1;
	return 0;
}

int get_trim_len(char *str)
{
    int i;
	int len;

	len = 0;
	i = 0;
	while(str[i])
	{
		if (is_redirect_characher(str[i]) && !is_redirect_characher(str[i + 1]))
		{
			i++;
			len++;
			while(str[i] == SPACE)
				i++;
		}
		len++;
		i++;
	}
    return (len);
}

char *trim_spaces (char *str)
{
	int i;
	int j;
	char *new_str;
	
	new_str = malloc((get_trim_len(str) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while(str[i])
	{
		if (is_redirect_characher(str[i]) && !is_redirect_characher(str[i + 1]))
		{
			new_str[j] = str[i];
			i++;
			j++;
			while(str[i] == SPACE)
				i++;
		}
		new_str[j] = str[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void fill_quotes(char *str, char c)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		if (str[i] == c)
		{
			i++;
			while(str[i] != c)
			{
				if (str[i] == SPACE)
					str[i] = GARBEGE;
				i++;
			}
		}
		i++;
	}
}