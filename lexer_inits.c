/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:49:48 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/06 14:33:57 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

lexer_t	*init_lexer(char *str)
{
	lexer_t	*lexer;

	lexer = malloc(sizeof(lexer_t));
	lexer->content = str;
	lexer->index = 0;
	lexer->c = str[lexer->index];
	return (lexer);
}

token_t	init_token(int type, char *value)
{
	token_t	token;

	token.type = type;
	token.value = value;
	return (token);
}

int	is_special_character(char c)
{
	if (c == PIPE || c == SPACE
		|| c == OLD_THAN || c == LESS_THAN
		|| c == AND || c == LEFT_PARENTHESES
		|| c == RIGHT_PARENTHESES || c == NEW_LINE)
		return (1);
	return (0);
}
