/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:36:40 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/08 12:03:28 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	lexer_get_string(t_lexer *lexer, char c, int t_tokenype)
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
	return (init_token(t_tokenype, val));
}

static t_token	lexer_get_word(t_lexer *lexer)
{
	int		i;
	char	*val;
	char	quote;

	val = ft_calloc((lexer_count_word(lexer) + 1), sizeof(char));
	i = 0;
	while (!is_special_character(lexer->c) && lexer->c != '\0')
	{
		if (lexer->c == SINGLE_QUOTES || lexer->c == DOUBLE_QUOTES)
		{
			quote = lexer->c;
			val[i++] = lexer->c;
			lexer_next_char(lexer);
			while (lexer->c != quote && lexer->c != '\0')
			{
				val[i++] = lexer->c;
				lexer_next_char(lexer);
			}
			val[i++] = lexer->c;
		}
		else
			val[i++] = lexer->c;
		lexer_next_char(lexer);
	}
	return (init_token(TOKEN_WORD, val));
}

static t_token	lexer_get_special_characters(t_lexer *lexer)
{
	if (lexer->c == OLD_THAN && lexer->content[lexer->index + 1] == OLD_THAN)
		return (init_token(TOKEN_GREAT_GREAT, ft_strdup(">>")));
	else if (lexer->c == LESS_THAN
		&& lexer->content[lexer->index + 1] == LESS_THAN)
		return (init_token(TOKEN_LESS_LESS, ft_strdup("<<")));
	else if (lexer->c == OLD_THAN)
		return (init_token(TOKEN_OLD_THAN, lexer_get_char_as_string(lexer->c)));
	else if (lexer->c == LESS_THAN)
		return (init_token(TOKEN_LESS_THAN,
				lexer_get_char_as_string(lexer->c)));
	else if (lexer->c == PIPE && lexer->content[lexer->index + 1] == PIPE)
		return (init_token(TOKEN_PIPE_PIPE, ft_strdup("||")));
	else if (lexer->c == AND && lexer->content[lexer->index + 1] == AND)
		return (init_token(TOKEN_AND_AND, ft_strdup("&&")));
	else if (lexer->c == AND && lexer->content[lexer->index + 1] != AND)
		parser_error("&", TOKEN_AND_AND);
	return (init_token(TOKEN_PIPE, lexer_get_char_as_string(lexer->c)));
}

static t_token	lexer_get_special_character_and_next(t_lexer *lexer)
{
	t_token	token;

	token = lexer_get_special_characters(lexer);
	lexer_next_char(lexer);
	if (token.e_type == TOKEN_LESS_LESS || token.e_type == TOKEN_GREAT_GREAT
		|| token.e_type == TOKEN_PIPE_PIPE || token.e_type == TOKEN_AND_AND)
		lexer_next_char(lexer);
	return (token);
}

t_token	lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == SPACE)
			lexer_skip_spaces(lexer);
		if (lexer->c == '\0')
			return (init_token(TOKEN_END, ft_strdup("")));
		if (lexer->c == LEFT_PARENTHESES)
			return (lexer_get_string(lexer, RIGHT_PARENTHESES, \
				TOKEN_PARENTHESES));
		if (!is_special_character(lexer->c))
			return (lexer_get_word(lexer));
		return (lexer_get_special_character_and_next(lexer));
	}
	return (init_token(TOKEN_END, ft_calloc(1, sizeof(char))));
}
