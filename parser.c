/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:09:20 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/14 15:53:18 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	parser_expect(t_lexer *lexer, int t_tokenype)
{
	t_token	new_token;

	new_token = lexer_get_next_token(lexer);
	if ((int)new_token.e_type == t_tokenype)
		return (new_token);
	else
		parser_error(new_token.value, new_token.e_type);
	return (new_token);
}

void	parser_parse(t_token *token, t_lexer *lexer)
{
	char	*str;

	str = g_data.cmds[g_data.index].str;
	if (token->e_type == TOKEN_WORD)
		parser_handle_word(token);
	else if (token->e_type == TOKEN_LESS_THAN)
	{
		g_data.cmds[g_data.index].inputs_str = join_with_sep(
				g_data.cmds[g_data.index].inputs_str,
				parser_expect(lexer, TOKEN_WORD).value, -1);
		g_data.cmds[g_data.index].heredoc = 0;
	}
	else if (token->e_type == TOKEN_LESS_LESS)
		parser_handle_heredoc(lexer);
	else if (token->e_type == TOKEN_END)
		return ;
	else
		parser_redirect(token, lexer);
}

void	init_data(char *str)
{
	int	i;

	g_data.num_of_cmds = get_num_of_cmds(str);
	g_data.index = 0;
	g_data.append = 0;
	g_data.err = 0;
	g_data.heredoc_signal = 0;
	g_data.child_signal = 0;
	g_data.close_heredoc = 0;
	g_data.cntr_c = 0;
	g_data.cmds = malloc(g_data.num_of_cmds * sizeof(t_cmd));
	i = -1;
	while (++i < g_data.num_of_cmds)
	{
		init_cmd_properties(i);
	}
}

int	check_parse_error(t_token token, t_token temp_token)
{
	if (is_commands_breaker(temp_token.e_type)
		&& (is_commands_breaker(token.e_type)))
	{
		parser_error(token.value, token.e_type);
		if (token.e_type != TOKEN_PARENTHESES)
			free(token.value);
		return (1);
	}
	return (0);
}

void	parser(char *str)
{
	t_lexer	*lexer;
	t_token	token;
	t_token	temp_token;

	init_data(str);
	lexer = init_lexer(str);
	token = lexer_get_next_token(lexer);
	parser_parse(&token, lexer);
	temp_token = token;
	if (token.e_type != TOKEN_PARENTHESES)
		free_if_exists(token.value);
	while (token.e_type)
	{
		token = lexer_get_next_token(lexer);
		if (check_parse_error(token, temp_token))
			break ;
		parser_parse(&token, lexer);
		temp_token = token;
		if (token.e_type != TOKEN_PARENTHESES)
			free(token.value);
	}
	free(lexer);
	get_path_and_args();
}
