/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:09:20 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/26 18:16:20 by yed-dyb          ###   ########.fr       */
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
		parser_error(new_token.value);
	return (new_token);
}


void	parser_parse(token_t *token, lexer_t *lexer)
{
	char	*str;

	str = data.cmds[data.index].str;
	if (token->type == TOKEN_WORD)
		parser_handle_word(token);
	else if (token->type == TOKEN_STRING_SINGLE_QUOTES)
		data.cmds[data.index].str = join_with_sep(str, token->value, -1);
	else if (token->type == TOKEN_STRING_DOUBLE_QUOTES)
		data.cmds[data.index].str = join_with_sep(str,
			parser_handle_string(token->value), -1);
	else if (token->type == TOKEN_PARENTHESES)
		data.cmds[data.index].str
			= join_with_sep(ft_strdup("./minishell"), token->value, -1);
	else if (token->type == TOKEN_END)
		return ;
	else
		parser_parse_2(token, lexer);
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
		i++;
	}
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
	free(token.value);
	while (token.type)
	{
		// printf("%s\n", token.value);
		token = lexer_get_next_token(lexer);
		if (parser_expect_new_line(temp_token.type) && token.type == TOKEN_END)
		{
			parser_error("NEW_LINE");
			break ;
		}
		parser_parse(&token, lexer);
		temp_token = token;
		free(token.value);
	}
	free(lexer);
	get_path_and_args();
}
