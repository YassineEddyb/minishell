/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:28:34 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/29 18:14:42 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_with_sep(char *s1, char *s2, char sep)
{
	char	*str;
	char	*tmp;
	char	*sep_str;

	sep_str = lexer_get_char_as_string(sep);
	tmp = ft_strjoin(s1, sep_str);
	free(sep_str);
	free(s1);
	str = ft_strjoin(tmp, s2);
	free(tmp);
	return (str);
}

int	get_num_of_cmds(char *str)
{
	int	i;
	int	len;
	char quote;

	i = 0;
	len = 1;
	while (str[i])
	{
		if (str[i] == LEFT_PARENTHESES)
		{
			if (str[i + 1] == RIGHT_PARENTHESES)
				parser_error(")");
			while (str[i] != RIGHT_PARENTHESES && str[i] != '\0')
			{
				// if (str[i] == '\0')
				// {
				// 	parser_error("NEW_LINE");
				// 	break;
				// }
				i++;
			}
		}
		if (str[i] == SINGLE_QUOTES || str[i] == DOUBLE_QUOTES)
		{
			quote = str[i++];
			while (str[i] != quote && str[i] != '\0')
				i++;
		}
		if ((str[i] == PIPE && str[i + 1] == PIPE)
			|| (str[i] == AND && str[i + 1] == AND))
		{
			i++;
			len++;
		}
		else if (str[i] == PIPE)
			len++;
		i++;
	}
	return (len);
}

void	clean_data(void)
{
	int	i;

	i = 0;
	data.append = 0;
	data.heredoc = 0;
	data.err = 0;
	data.input = NULL;
	while (i < data.num_of_cmds)
	{
		free(data.cmds[i].str);
		free(data.cmds[i].path);
		free_arr(data.cmds[i].args);
		if (data.input)
			free(data.input);
		if (data.cmds[i].output)
			free(data.cmds[i].output);
		data.cmds[i].output = NULL;
		data.cmds[i].and = 0;
		data.cmds[i].or = 0;
		data.cmds[i].pipe = 0;
		i++;
	}
}
