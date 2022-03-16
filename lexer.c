/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:36:40 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/16 12:34:10 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

lexer_t *init_lexer(char *str)
{
    lexer_t *lexer;
    lexer = malloc(sizeof(lexer_t));
    lexer->content = str;
    lexer->index = 0;
    lexer->c = str[lexer->index];

    return (lexer);
}

static token_t lexer_get_string(lexer_t *lexer, char c)
{
    int i;
    char *val;
    token_t token;
    lexer_next_char(lexer);

    val = malloc(lexer_strlen(lexer, c) + 1 * sizeof(char));
    i = 0;
    while(lexer->c != c && lexer->c != '\0')
    {
        val[i] = lexer->c;
        lexer_next_char(lexer);
        i++;
    }
    lexer_next_char(lexer);
    val[i] = '\0';
    if (c == DOUBLE_QUOTES)
        token = init_token(TOKEN_STRING_DOUBLE_QUOTES, val);
    else if (c == SINGLE_QUOTES)
        token = init_token(TOKEN_STRING_SINGLE_QUOTES, val);
    return (token);
}

static token_t lexer_get_word(lexer_t *lexer)
{
    int i;
    char *val;

    val = malloc(lexer_strlen(lexer, SPACE) + 1 * sizeof(char));
    i = 0;
    while(lexer->c != SPACE && lexer->c != '\0')
    {
        val[i] = lexer->c;
        lexer_next_char(lexer);
        i++;
    }
    val[i] = '\0';
    return (init_token(TOKEN_WORD, val));
}


static token_t lexer_get_special_characters(lexer_t *lexer)
{
    if (lexer->c == OLD_THAN)
        return (init_token(TOKEN_OLD_THAN, lexer_get_char_as_string(lexer->c)));
    else if (lexer->c == LESS_THAN)
        return (init_token(TOKEN_OLD_THAN, lexer_get_char_as_string(lexer->c)));
    else if (lexer->c == PIPE)
        return (init_token(TOKEN_PIPE, lexer_get_char_as_string(lexer->c)));
    else
        return (init_token(TOKEN_DOLLAR_SIGN, lexer_get_char_as_string(lexer->c)));
}

static token_t lexer_get_special_character_and_next(lexer_t *lexer)
{
    token_t token;
    token = lexer_get_special_characters(lexer);
    lexer_next_char(lexer);
    return token;
}

token_t lexer_get_next_token(lexer_t *lexer)
{
    while(lexer->c != '\0')
    {
        if (lexer->c == SPACE)
            lexer_skip_spaces(lexer);
        if (lexer->c == DOUBLE_QUOTES)
            return lexer_get_string(lexer, DOUBLE_QUOTES);
        if (lexer->c == SINGLE_QUOTES)
            return lexer_get_string(lexer, SINGLE_QUOTES);
        if(!is_special_character(lexer->c))
            return lexer_get_word(lexer);
        return lexer_get_special_character_and_next(lexer);
    }
    return init_token(TOKEN_END, ft_calloc(1, sizeof(char)));
}