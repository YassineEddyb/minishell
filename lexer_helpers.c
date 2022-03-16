/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:54:57 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/16 13:07:27 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

token_t init_token(int type, char *value)
{
    token_t token;

    //token = malloc(sizeof(token_t));
    token.type = type;
    token.value = value;

    return (token);
}

int lexer_strlen(lexer_t *lexer, char c)
{
    int i;
    int len;

    i = lexer->index;
    len = 0;
    while(lexer->content[i] != c && lexer->content[i]!= '\0')
    {
        i++;
        len++;
    }
    return (len);
}

void lexer_next_char(lexer_t *lexer)
{
    if (lexer->c != '\0')
    {
        (lexer->index)++;
        lexer->c = lexer->content[lexer->index];
    }
}

void lexer_skip_spaces(lexer_t *lexer)
{
    while(lexer->c == SPACE)
    {
        lexer_next_char(lexer);
    }
}

char *lexer_get_char_as_string(char c)
{
    char *str;

    str = malloc(2 * sizeof(char));
    str[0] = c;
    str[1] = '\0';
    return (str);
}

int is_special_character(char c)
{
    if (c == DOUBLE_QUOTES || c == SINGLE_QUOTES\
            || c == DOLLAR_SIGN || c == PIPE\
            || c == OLD_THAN || c == LESS_THAN)
        return (1);
    return (0);
}