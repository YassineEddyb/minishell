/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:13:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/08 12:56:18 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parser_collect_word(t_lexer *lexer, char c)
{
	int		i;
	char	*val;

	val = malloc((lexer_strlen(lexer, c) + 1) * sizeof(char));
	i = 0;
	while (lexer->c != c && lexer->c != SINGLE_QUOTES
		&& lexer->c != DOUBLE_QUOTES && lexer->c != '\0')
	{
		val[i] = lexer->c;
		lexer_next_char(lexer);
		i++;
	}
	val[i] = '\0';
	return (val);
}

static char	*parser_collect_dollar_sign_string(t_lexer *lexer)
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

char	*get_env_value(t_lexer *lexer)
{
	char	*str;
	char	*tmp;

	lexer_next_char(lexer);
	if (lexer->c == '\0')
		str = ft_strdup("$");
	else if (lexer->c == QUESTION_MARK)
	{
		str = ft_itoa(g_data.exit_code);
		lexer_next_char(lexer);
	}
	else
	{
		tmp = parser_collect_dollar_sign_string(lexer);
		str = get_env_variable(tmp);
		free(tmp);
	}
	return (str);
}

static char	*parser_collect_string(t_lexer *lexer, char c)
{
	int		i;
	char	*val;

	val = NULL;
	lexer_next_char(lexer);
	while (lexer->c != c && lexer->c != '\0')
	{
		if (lexer->c == DOLLAR_SIGN
			&& (is_surrounded_with_qoutes(lexer)
				|| !ft_isalnum(lexer->content[lexer->index + 1])))
		{
			val = join_and_free(val, ft_strdup("$"));
			lexer_next_char(lexer);
		}
		else if (c == DOUBLE_QUOTES && lexer->c == DOLLAR_SIGN)
			val = join_and_free(val, get_env_value(lexer));
		else
		{
			val = join_and_free(val, lexer_get_char_as_string(lexer->c));
			lexer_next_char(lexer);
		}
	}
	if (lexer->c == SINGLE_QUOTES || lexer->c == DOUBLE_QUOTES)
		lexer_next_char(lexer);
	return (val);
}

char	*parser_handle_dollar_sign(char *value)
{
	char	*str;
	t_lexer	*lexer;

	str = NULL;
	lexer = init_lexer(value);
	while (lexer->c != '\0')
	{
		if (lexer->c != DOLLAR_SIGN)
			str = join_and_free(str,
					parser_collect_word(lexer, DOLLAR_SIGN));
		if (lexer->c == SINGLE_QUOTES || lexer->c == DOUBLE_QUOTES)
			str = join_and_free(str, parser_collect_string(lexer, lexer->c));
		else if (lexer->c == DOLLAR_SIGN)
			str = join_and_free(str, get_env_value(lexer));
	}
	free(lexer);
	return (str);
}
