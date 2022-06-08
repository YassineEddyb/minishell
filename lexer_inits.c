/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:49:48 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/08 12:14:21 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer(char *str)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->content = str;
	lexer->index = 0;
	lexer->c = str[lexer->index];
	return (lexer);
}

t_token	init_token(int type, char *value)
{
	t_token	token;

	token.e_type = type;
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
