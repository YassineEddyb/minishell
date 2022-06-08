/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:09:20 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/08 12:57:56 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	parser_expect(t_lexer *lexer, int t_tokenype)
{
	t_token	new_token;

	new_token = lexer_get_next_token(lexer);
	if (new_token.e_type == t_tokenype)
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
	else if (token->e_type == TOKEN_PARENTHESES)
	{
		if (!g_data.err)
			g_data.cmds[g_data.index].str
				= join_with_sep(ft_strdup("./minishell"), token->value, -1);
	}
	else if (token->e_type == TOKEN_LESS_THAN)
	{
		free_if_exists(g_data.cmds[g_data.index].input);
		g_data.cmds[g_data.index].input
			= parser_expect(lexer, TOKEN_WORD).value;
		g_data.heredoc = 0;
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
	g_data.heredoc = 0;
	g_data.append = 0;
	g_data.err = 0;
	g_data.cmds = malloc(g_data.num_of_cmds * sizeof(t_cmd));
	i = 0;
	while (i < g_data.num_of_cmds)
	{
		g_data.cmds[i].pipe = 0;
		g_data.cmds[i].and = 0;
		g_data.cmds[i].or = 0;
		g_data.cmds[i].args = NULL;
		g_data.cmds[i].str = NULL;
		g_data.cmds[i].path = NULL;
		g_data.cmds[i].output = NULL;
		g_data.cmds[i].input = NULL;
		i++;
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
