/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:45:32 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/08 19:34:49 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_stop_charaters(char c)
{
	if (!ft_isalnum(c))
		return (1);
	return (0);
}

int	parser_count_word(t_lexer *lexer)
{
	int	i;
	int	len;

	i = lexer->index;
	len = 0;
	while (!is_stop_charaters(lexer->content[i])
		&& lexer->content[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char	*get_env_variable(char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = join_and_free(ft_strdup(var), ft_strdup("="));
	while (g_data.env[i])
	{
		if (!ft_strncmp(tmp, g_data.env[i], ft_strlen(var) + 1))
		{
			free(tmp);
			return (ft_substr(g_data.env[i], ft_strlen(var) + 1,
					ft_strlen(g_data.env[i]) - ft_strlen(var) + 1));
		}
		i++;
	}
	free(tmp);
	return (ft_strdup(""));
}

int	is_surrounded_with_qoutes(t_lexer *lexer)
{
	if ((lexer->index > 0
			&& lexer->content[lexer->index + 1] == DOUBLE_QUOTES
			&& lexer->content[lexer->index - 1] == DOUBLE_QUOTES)
		|| (lexer->index > 0
			&& lexer->content[lexer->index + 1] == SINGLE_QUOTES
			&& lexer->content[lexer->index - 1] == SINGLE_QUOTES))
		return (1);
	return (0);
}

int	is_empty_string(char *str)
{
	if (!ft_strncmp(str, "\"\"", ft_strlen(str))
		|| !ft_strncmp(str, "\'\'", ft_strlen(str)))
		return (1);
	return (0);
}
