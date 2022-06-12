/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:13:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/12 11:07:57 by yed-dyb          ###   ########.fr       */
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
	while (ft_isalnum(lexer->c) && lexer->c != '\0')
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
	if (lexer->c == QUESTION_MARK)
	{
		str = ft_itoa(g_data.exit_code);
		lexer_next_char(lexer);
	}
	else if (lexer->c == '\0' || (lexer->c != SINGLE_QUOTES
			&& lexer->c != DOUBLE_QUOTES
			&& !ft_isalnum(lexer->content[lexer->index])))
		str = ft_strdup("$");
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
	while (lexer->c != c)
	{
		if (lexer->c == '\0')
		{
			ft_putstr_fd("minishell: unclosed quotes\n", 2);
			g_data.err = 1;
			break ;
		}
		val = join_and_free(val, parse_string(c, lexer));
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
