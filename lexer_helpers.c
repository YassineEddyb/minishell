/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:54:57 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/08 12:03:13 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_strlen(t_lexer *lexer, char c)
{
	int	i;
	int	len;

	i = lexer->index;
	len = 0;
	while (lexer->content[i] != c && lexer->content[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

int	lexer_count_word(t_lexer *lexer)
{
	int		i;
	int		len;
	char	quote;

	i = lexer->index;
	len = 0;
	while (!is_special_character(lexer->content[i])
		&& lexer->content[i] != '\0')
	{
		if (lexer->content[i] == SINGLE_QUOTES
			|| lexer->content[i] == DOUBLE_QUOTES)
		{
			quote = lexer->content[i];
			i++;
			len++;
			while (lexer->content[i] != quote && lexer->content[i] != '\0')
			{
				i++;
				len++;
			}
		}
		i++;
		len++;
	}
	return (len);
}

void	lexer_next_char(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		(lexer->index)++;
		lexer->c = lexer->content[lexer->index];
	}
}

void	lexer_skip_spaces(t_lexer *lexer)
{
	while (lexer->c == SPACE)
		lexer_next_char(lexer);
}

char	*lexer_get_char_as_string(char c)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}
