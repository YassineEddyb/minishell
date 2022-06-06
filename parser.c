/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:09:20 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/06 12:22:09 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

token_t	parser_expect(lexer_t *lexer, int token_type)
{
	token_t	new_token;

	new_token = lexer_get_next_token(lexer);
	if (new_token.type == token_type)
		return (new_token);
	else
		parser_error(new_token.value, new_token.type);
	return (new_token);
}

void	parser_parse(token_t *token, lexer_t *lexer)
{
	char	*str;

	str = data.cmds[data.index].str;
	if (token->type == TOKEN_WORD)
		parser_handle_word(token);
	else if (token->type == TOKEN_PARENTHESES)
	{
		if (!data.err)
			data.cmds[data.index].str
				= join_with_sep(ft_strdup("./minishell"), token->value, -1);
	}
	else if (token->type == TOKEN_LESS_THAN)
	{
		free_if_exists(data.cmds[data.index].input);
		data.cmds[data.index].input = parser_expect(lexer, TOKEN_WORD).value;
		data.heredoc = 0;
	}
	else if (token->type == TOKEN_LESS_LESS)
		parser_handle_heredoc(lexer);
	else if (token->type == TOKEN_END)
		return ;
	else
		parser_redirect(token, lexer);
}

void	init_data(char *str)
{
	int	i;

	data.num_of_cmds = get_num_of_cmds(str);
	data.index = 0;
	data.heredoc = 0;
	data.append = 0;
	data.err = 0;
	data.cmds = malloc(data.num_of_cmds * sizeof(t_cmd));
	i = 0;
	while (i < data.num_of_cmds)
	{
		data.cmds[i].pipe = 0;
		data.cmds[i].and = 0;
		data.cmds[i].or = 0;
		data.cmds[i].args = NULL;
		data.cmds[i].str = NULL;
		data.cmds[i].path = NULL;
		data.cmds[i].output = NULL;
		data.cmds[i].input = NULL;
		i++;
	}
}

int	check_parse_error(token_t token, token_t temp_token)
{
	if (is_commands_breaker(temp_token.type)
		&& (is_commands_breaker(token.type)))
	{
		parser_error(token.value, token.type);
		if (token.type != TOKEN_PARENTHESES)
			free(token.value);
		return (1);
	}
	return (0);
}

void	parser(char *str)
{
	lexer_t	*lexer;
	token_t	token;
	token_t	temp_token;

	init_data(str);
	lexer = init_lexer(str);
	token = lexer_get_next_token(lexer);
	parser_parse(&token, lexer);
	temp_token = token;
	if (token.type != TOKEN_PARENTHESES)
		free_if_exists(token.value);
	while (token.type)
	{
		token = lexer_get_next_token(lexer);
		if (check_parse_error(token, temp_token))
			break ;
		parser_parse(&token, lexer);
		temp_token = token;
		if (token.type != TOKEN_PARENTHESES)
			free(token.value);
	}
	free(lexer);
	get_path_and_args();
}
