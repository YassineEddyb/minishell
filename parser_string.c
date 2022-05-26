/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:13:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/26 13:11:26 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_stop_charaters(char c) {
	if (c >= 32 && c <= 47)
		return (1);
	return (0);
}

int	parser_count_word(lexer_t *lexer)
{
	int	i;
	int	len;

	i = lexer->index;
	len = 0;
	while (!is_stop_charaters(lexer->content[i]) && lexer->content[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static char	*parser_collect_string(lexer_t *lexer, char c)
{
	int		i;
	char	*val;

	val = malloc((lexer_strlen(lexer, c) + 1) * sizeof(char));
	i = 0;
	while (lexer->c != c && lexer->c != '\0')
	{
		val[i] = lexer->c;
		lexer_next_char(lexer);
		i++;
	}
	val[i] = '\0';
	return (val);
}

static char *parser_collect_dollar_sign_string(lexer_t *lexer)
{
	int		i;
	char	*val;

	i = 0;
	val = malloc((parser_count_word(lexer) + 1) * sizeof(char));

	while (!is_stop_charaters(lexer->c) && lexer->c != '\0')
	{
		val[i] = lexer->c;
		lexer_next_char(lexer);
		i++;
	}
	val[i] = '\0';
	return (val);
}

char	*parser_handle_string(char *value)
{
	char	*str;
	lexer_t	*lexer;

	str = NULL; 
	lexer = init_lexer(value);
	while (lexer->c != '\0')
	{
		if (lexer->c != DOLLAR_SIGN)
			str = ft_strjoin(str, parser_collect_string(lexer, DOLLAR_SIGN));
		else if (lexer->c == DOLLAR_SIGN && is_stop_charaters(lexer->content[lexer->index + 1]))
		{
			str = ft_strjoin(str, ft_strdup("$"));
			lexer_next_char(lexer);
		}
		else if (lexer->c == DOLLAR_SIGN)
		{
			lexer_next_char(lexer);
			if (lexer->c == QUESTION_MARK)
			{
				str = ft_strjoin(str, ft_itoa(data.exit_code));
				lexer_next_char(lexer);
			}
			else
				str = ft_strjoin(str, getenv(
					parser_collect_dollar_sign_string(lexer)));
		}
	}
	free(lexer);
	return (str);
}
