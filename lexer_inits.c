/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:49:48 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/04/10 18:06:15 by yed-dyb          ###   ########.fr       */
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
