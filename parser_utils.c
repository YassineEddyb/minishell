/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:28:34 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/11 18:53:38 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_with_sep(char *s1, char *s2, char sep)
{
	char	*str;
	char	*tmp;

	tmp = join_and_free(s1, lexer_get_char_as_string(sep));
	str = join_and_free(tmp, s2);
	return (str);
}

void	skip_strings(char *str, int *i)
{
	char	quote;

	if (str[*i] == LEFT_PARENTHESES)
	{
		if (str[*i + 1] == RIGHT_PARENTHESES)
			parser_error(")", TOKEN_PARENTHESES);
		while (str[*i] != RIGHT_PARENTHESES && str[*i] != '\0')
			(*i)++;
	}
	if (str[*i] == SINGLE_QUOTES || str[*i] == DOUBLE_QUOTES)
	{
		quote = str[(*i)++];
		while (str[*i] != quote && str[*i] != '\0')
			(*i)++;
	}
}

int	get_num_of_cmds(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = 1;
	while (str[i])
	{
		skip_strings(str, &i);
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
	while (i < g_data.num_of_cmds)
	{
		free(g_data.cmds[i].str);
		free(g_data.cmds[i].path);
		free_arr(g_data.cmds[i].args);
		free_if_exists(g_data.cmds[i].output);
		free_if_exists(g_data.cmds[i].inputs_str);
		free_arr(g_data.cmds[i].inputs);
		i++;
	}
	free(g_data.cmds);
}

void	parser_error(char *value, int t_tokenype)
{
	if (!g_data.err)
	{
		ft_putstr_fd("minishell: syntax error near unexepcted token '", STDERR);
		if (t_tokenype == TOKEN_END)
			ft_putstr_fd("NEW_LINE", STDERR);
		else
			ft_putstr_fd(value, STDERR);
		ft_putstr_fd("'\n", STDERR);
		g_data.exit_code = 258;
		g_data.err = 1;
	}
}
