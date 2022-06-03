/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:13:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/03 10:20:20 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_stop_charaters(char c, int quote) {
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
	while (!is_stop_charaters(lexer->content[i], 0) && lexer->content[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static char	*parser_collect_word(lexer_t *lexer, char c, int quote)
{
	int		i;
	char	*val;

	val = malloc((lexer_strlen(lexer, c) + 1) * sizeof(char));
	i = 0;
	while (lexer->c != c && (!quote || lexer->c != SINGLE_QUOTES) && lexer->c != '\0')
	{
		if (quote && lexer->c == DOUBLE_QUOTES)
			lexer_next_char(lexer);
		else
		{
			val[i] = lexer->c;
			lexer_next_char(lexer);
			i++;
		}
	}
	val[i] = '\0';
	return (val);
}

static char	*parser_collect_string(lexer_t *lexer, char c)
{
	int		i;
	char	*val;

	lexer_next_char(lexer);
	val = malloc((lexer_strlen(lexer, c) + 1) * sizeof(char));
	i = 0;
	while (lexer->c != c && lexer->c != '\0')
	{
		val[i] = lexer->c;
		lexer_next_char(lexer);
		i++;
	}
	lexer_next_char(lexer);
	val[i] = '\0';
	return (val);
}

static char *parser_collect_dollar_sign_string(lexer_t *lexer)
{
	int		i;
	char	*val;

	i = 0;
	val = malloc((parser_count_word(lexer) + 1) * sizeof(char));

	while (!is_stop_charaters(lexer->c, 0) && lexer->c != '\0')
	{
		val[i] = lexer->c;
		lexer_next_char(lexer);
		i++;
	}
	val[i] = '\0';
	return (val);
}

int is_surrounded_with_qoutes(lexer_t *lexer) {
	if ((lexer->index > 0 && lexer->content[lexer->index + 1] == DOUBLE_QUOTES 
		&& lexer->content[lexer->index - 1] == DOUBLE_QUOTES) 
		|| (lexer->index > 0 && lexer->content[lexer->index + 1] == SINGLE_QUOTES 
		&& lexer->content[lexer->index - 1] == SINGLE_QUOTES))
		return (1);
	return (0);
}

char	*parser_handle_dollar_sign(char *value, int quote)
{
	char	*str;
	char	*tmp;
	lexer_t	*lexer;

	str = NULL;
	if (!ft_strncmp(value, "\"\"", ft_strlen(value)) || !ft_strncmp(value, "\'\'", ft_strlen(value)))
		return (lexer_get_char_as_string(-2));
	lexer = init_lexer(value);
	while (lexer->c != '\0')
	{
		if (lexer->c != DOLLAR_SIGN)
			str = join_and_free(str, parser_collect_word(lexer, DOLLAR_SIGN, quote));
		if (quote && lexer->c == SINGLE_QUOTES)
			str = join_and_free(str, parser_collect_string(lexer, SINGLE_QUOTES));
		else if (lexer->c == DOLLAR_SIGN && (!quote || is_surrounded_with_qoutes(lexer) 
			|| is_stop_charaters(lexer->content[lexer->index + 1], 1)))
		{
			str = join_and_free(str, ft_strdup("$"));
			lexer_next_char(lexer);
		}
		else if (lexer->c == DOLLAR_SIGN)
		{
			lexer_next_char(lexer);
			if (lexer->c == QUESTION_MARK)
			{
				str = join_and_free(str, ft_itoa(data.exit_code));
				lexer_next_char(lexer);
			}
			else
			{
				tmp  = parser_collect_dollar_sign_string(lexer);
				str = ft_str_join(str, getenv(tmp));
				free(tmp);
			}
		}
	}
	free(lexer);
	return (str);
}