/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:09:23 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/29 18:04:34 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_redirect(token_t *token, lexer_t *lexer)
{
	if (token->type == TOKEN_LESS_THAN)
		data.input = parser_expect(lexer, TOKEN_WORD).value;
	else if (token->type == TOKEN_OLD_THAN) {
		data.cmds[data.index].output = parser_expect(
				lexer, TOKEN_WORD).value;
		if (!data.err)
			open(data.cmds[data.index].output, O_RDWR | O_CREAT, 0644);
	}
	else if (token->type == TOKEN_LESS_LESS)
		parser_handle_heredoc(lexer);
	else if (token->type == TOKEN_GREAT_GREAT)
	{
		data.append = 1;
		data.cmds[data.index].output = parser_expect(
				lexer, TOKEN_WORD).value;
		if (!data.err)
			open(data.cmds[data.index].output, O_RDWR | O_CREAT, 0644);
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
				data.cmds[data.index].str, parser_handle_dollar_sign(token->value, 1), -1);
}

char *remove_quotes(char *str) {
	int i = 0;
	int j = 0;
	int len;
	char quote = 0;
	char *new;

	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));

	while(str[i])
	{
		if (!quote && (str[i] == SINGLE_QUOTES || str[i] == DOUBLE_QUOTES))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else {
			new[j] = str[i];
			j++;
		}
		i++;
	}

	return (new);
}

void	parser_handle_heredoc(lexer_t *lexer)
{

	data.limit = parser_expect(lexer, TOKEN_WORD).value;
	if (ft_strchr(data.limit, DOUBLE_QUOTES) || ft_strchr(data.limit, SINGLE_QUOTES))
		data.heredoc = 2;
	else
		data.heredoc = 1;
	data.limit = remove_quotes(data.limit);
	here_doc();
	data.input = NULL;
}

void	parser_error(char *value)
{
	ft_putstr_fd("minishell: syntax error near unexepcted token '", STDERR);
	if (value[0] == '\0')
		ft_putstr_fd("NEW_LINE", STDERR);
	else 
		ft_putstr_fd(value, STDERR);
	ft_putstr_fd("'\n", STDERR);
	data.exit_code = 258;
	data.err = 1;
}

int	is_commands_breaker(int n)
{
	if (n == TOKEN_PIPE || n == TOKEN_PIPE_PIPE
		|| n == TOKEN_AND_AND || n == TOKEN_END)
		return (1);
	return (0);
}
