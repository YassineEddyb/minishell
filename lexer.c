/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:36:40 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/25 16:18:36 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static token_t	lexer_get_string(lexer_t *lexer, char c, int token_type)
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
	return (init_token(token_type, val));
}

static token_t	lexer_get_word(lexer_t *lexer)
{
	int		i;
	char	*val;

	val = malloc((lexer_count_word(lexer) + 1) * sizeof(char));
	i = 0;
	while (!is_special_character(lexer->c) && lexer->c != SPACE && lexer->c != '\0')
	{
		val[i] = lexer->c;
		lexer_next_char(lexer);
		i++;
	}
	val[i] = '\0';
	return (init_token(TOKEN_WORD, val));
}

static token_t	lexer_get_special_characters(lexer_t *lexer)
{
	if (lexer->c == OLD_THAN && lexer->content[lexer->index + 1] == OLD_THAN)
		return (init_token(TOKEN_GREAT_GREAT, ft_strdup(">>")));
	else if (lexer->c == LESS_THAN
		&& lexer->content[lexer->index + 1] == LESS_THAN)
		return (init_token(TOKEN_LESS_LESS, ft_strdup("<<")));
	else if (lexer->c == OLD_THAN)
		return (init_token(TOKEN_OLD_THAN, lexer_get_char_as_string(lexer->c)));
	else if (lexer->c == LESS_THAN)
		return (init_token(TOKEN_LESS_THAN, \
			lexer_get_char_as_string(lexer->c)));
	else if (lexer->c == PIPE && lexer->content[lexer->index + 1] == PIPE)
		return (init_token(TOKEN_PIPE_PIPE, ft_strdup("||")));
	else if (lexer->c == AND && lexer->content[lexer->index + 1] == AND)
		return (init_token(TOKEN_AND_AND, ft_strdup("&&")));
	else if (lexer->c == PIPE)
		return (init_token(TOKEN_PIPE, lexer_get_char_as_string(lexer->c)));
	return (init_token(TOKEN_NEW_LINE, ft_strdup("\n")));
}

static token_t	lexer_get_special_character_and_next(lexer_t *lexer)
{
	token_t	token;

	token = lexer_get_special_characters(lexer);
	lexer_next_char(lexer);
	if (token.type == TOKEN_LESS_LESS || token.type == TOKEN_GREAT_GREAT
		|| token.type == TOKEN_PIPE_PIPE || token.type == TOKEN_AND_AND)
		lexer_next_char(lexer);
	return (token);
}

token_t	lexer_get_next_token(lexer_t *lexer)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == SPACE)
			lexer_skip_spaces(lexer);
		if (lexer->c == DOUBLE_QUOTES)
			return (lexer_get_string(lexer, DOUBLE_QUOTES, \
				TOKEN_STRING_DOUBLE_QUOTES));
		if (lexer->c == SINGLE_QUOTES)
			return (lexer_get_string(lexer, SINGLE_QUOTES, \
				TOKEN_STRING_SINGLE_QUOTES));
		if (lexer->c == LEFT_PARENTHESES)
			return (lexer_get_string(lexer, RIGHT_PARENTHESES, \
				TOKEN_PARENTHESES));
		if (!is_special_character(lexer->c))
			return (lexer_get_word(lexer));
		return (lexer_get_special_character_and_next(lexer));
	}
	return (init_token(TOKEN_END, ft_calloc(1, sizeof(char))));
}
