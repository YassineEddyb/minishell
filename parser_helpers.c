/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:45:32 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/06 11:11:27 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_stop_charaters(char c, int quote)
{
	if (quote && (c == SINGLE_QUOTES || c == DOUBLE_QUOTES))
		return (0);
	if ((c >= 32 && c <= 47) || c == '\0')
		return (1);
	return (0);
}

int	parser_count_word(lexer_t *lexer)
{
	int	i;
	int	len;

	i = lexer->index;
	len = 0;
	while (!is_stop_charaters(lexer->content[i], 0)
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
	tmp = ft_strjoin(var, "=");
	while (data.env[i])
	{
		if (!ft_strncmp(tmp, data.env[i], ft_strlen(var) + 1))
		{
			free(tmp);
			return (ft_substr(data.env[i], ft_strlen(var) + 1,
					ft_strlen(data.env[i]) - ft_strlen(var) + 1));
		}
		i++;
	}
	free(tmp);
	return (ft_strdup(""));
}

int	is_surrounded_with_qoutes(lexer_t *lexer)
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
