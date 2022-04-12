/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:09:23 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/04/11 01:27:18 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_parse_2(token_t *token, lexer_t *lexer)
{
	if (token->type == TOKEN_LESS_THAN)
		data.input = parser_expect(lexer, TOKEN_WORD).value;
	else if (token->type == TOKEN_OLD_THAN)
		data.cmds[data.index].output = parser_expect(
				lexer, TOKEN_WORD).value;
	else if (token->type == TOKEN_LESS_LESS)
		parser_handle_append_redirect(lexer);
	else if (token->type == TOKEN_GREAT_GREAT)
	{
		data.append = 1;
		data.cmds[data.index].output = parser_expect(
				lexer, TOKEN_WORD).value;
	}
	else if (token->type == TOKEN_PIPE_PIPE)
		data.cmds[data.index].or = 1;
	else if (token->type == TOKEN_AND_AND)
		data.cmds[data.index].and = 1;
	else if (token->type == TOKEN_PIPE)
		data.cmds[data.index].pipe = 1;
	if (token->type == TOKEN_AND_AND || token->type == TOKEN_PIPE
		||token->type == TOKEN_PIPE_PIPE)
		data.index++;
}

void	parser_handle_word(token_t *token)
{
	if (ft_strchr(token->value, ASTERISK))
		parser_check_asterisk(token);
	else
		data.cmds[data.index].str = join_with_sep(
				data.cmds[data.index].str, token->value, -1);
}

void	parser_handle_append_redirect(lexer_t *lexer)
{
	data.heredoc = 1;
	data.limit = parser_expect(lexer, TOKEN_WORD).value;
	data.input = NULL;
	if (data.cmds[0].str == NULL)
	{
		data.cmds[0].path = ft_strdup("/bin/cat");
		data.cmds[0].args = ft_calloc(2, sizeof(char *));
		data.cmds[0].args[0] = ft_strdup("cat");
	}
}

void	parser_error(char *value)
{
	ft_putstr_fd("minishell: syntax error near unexepcted token '", STDERR);
	ft_putstr_fd(value, STDERR);
	ft_putstr_fd("'\n", STDERR);
	data.exit_code = 258;
	data.err = 1;
}

int	parser_expect_new_line(int n)
{
	if (n == TOKEN_PIPE || n == TOKEN_PIPE_PIPE
		|| n == TOKEN_AND_AND)
		return (1);
	return (0);
}
