/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:13:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/04/08 21:14:19 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *parser_collect_string(lexer_t *lexer, char c)
{
    int i;
    char *val;

    val = malloc(lexer_strlen(lexer, c) + 1 * sizeof(char));
    i = 0;
    while(lexer->c != c && lexer->c != '\0')
    {
        val[i] = lexer->c;
        lexer_next_char(lexer);
        i++;
    }
    val[i] = '\0';
    return (val);
}

char *parser_handle_string(token_t *token)
{
    int i;
    char *str = NULL;
    lexer_t *lexer = init_lexer(token->value);

    while(lexer->c != '\0')
    {
        if (lexer->c != DOLLAR_SIGN)
            str = ft_strjoin(str ,parser_collect_string(lexer, DOLLAR_SIGN));
        else if (lexer->c == DOLLAR_SIGN)
        {
            lexer_next_char(lexer);
			if (lexer->c == QUESTION_MARK)
			{
				str = ft_strjoin(str, ft_itoa(data.exit_code));
				lexer_next_char(lexer);
			}
			else
           		str = ft_strjoin(str,getenv(parser_collect_string(lexer, SPACE)));
        }
    }
    free(lexer);
    return (str);
}