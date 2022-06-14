/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 10:26:21 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/14 21:40:13 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_properties(int i)
{
	g_data.cmds[i].pipe = 0;
	g_data.cmds[i].and = 0;
	g_data.cmds[i].or = 0;
	g_data.cmds[i].args = NULL;
	g_data.cmds[i].str = NULL;
	g_data.cmds[i].path = NULL;
	g_data.cmds[i].output = NULL;
	g_data.cmds[i].input = NULL;
	g_data.cmds[i].heredoc = 0;
	g_data.cmds[i].append = 0;
	g_data.cmds[i].err = 0;
}

int	print_dollar_sign(t_lexer *lexer)
{
	if (lexer->c == DOLLAR_SIGN
		&& (is_surrounded_with_qoutes(lexer)
			|| !ft_isalnum(lexer->content[lexer->index + 1]))
		&& lexer->content[lexer->index + 1] != QUESTION_MARK
		&& lexer->content[lexer->index + 1] != '_')
		return (1);
	return (0);
}

char	*parse_string(char c, t_lexer *lexer)
{
	char	*val;

	val = NULL;
	if (print_dollar_sign(lexer))
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
	return (val);
}
