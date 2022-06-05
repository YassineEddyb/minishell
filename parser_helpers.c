/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:09:23 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/03 16:33:29 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_redirect(token_t *token, lexer_t *lexer)
{
	if (token->type == TOKEN_LESS_THAN)
	{
		free_if_exists(data.cmds[data.index].input);
		data.cmds[data.index].input = parser_expect(lexer, TOKEN_WORD).value;
		data.heredoc = 0;
	}
	else if (token->type == TOKEN_OLD_THAN) {
		free_if_exists(data.cmds[data.index].output);
		data.cmds[data.index].output = parser_expect(
				lexer, TOKEN_WORD).value;
		data.append = 0;
		if (!data.err)
			open(data.cmds[data.index].output, O_RDWR | O_CREAT, 0644);
	}
	else if (token->type == TOKEN_LESS_LESS)
		parser_handle_heredoc(lexer);
	else if (token->type == TOKEN_GREAT_GREAT)
	{
		data.append = 1;
		free_if_exists(data.cmds[data.index].output);
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
	{
		if (!ft_strncmp(token->value, "\"\"", ft_strlen(token->value)) 
			|| !ft_strncmp(token->value, "\'\'", ft_strlen(token->value)))
			data.cmds[data.index].str = join_with_sep(
					data.cmds[data.index].str, lexer_get_char_as_string(-2), -1);
		else 
			data.cmds[data.index].str = join_with_sep(
					data.cmds[data.index].str, parser_handle_dollar_sign(token->value, 1), -1);
	}
}

char *remove_quotes(char *str) {
	int i = 0;
	int j = 0;
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
	char *tmp;
	tmp = parser_expect(lexer, TOKEN_WORD).value;
	if (ft_strchr(tmp, DOUBLE_QUOTES) || ft_strchr(tmp, SINGLE_QUOTES))
		data.heredoc = 2;
	else
		data.heredoc = 1;
	data.limit = remove_quotes(tmp);
	free(tmp);
	here_doc();
	free_if_exists(data.cmds[data.index].input);
}

void	parser_error(char *value, int token_type)
{
	if (!data.err)
	{
		ft_putstr_fd("minishell: syntax error near unexepcted token '", STDERR);
		if (token_type == TOKEN_END)
			ft_putstr_fd("NEW_LINE", STDERR);
		else 
			ft_putstr_fd(value, STDERR);
		ft_putstr_fd("'\n", STDERR);
		data.exit_code = 258;
		data.err = 1;
	}
}

int	is_commands_breaker(int n)
{
	if (n == TOKEN_PIPE || n == TOKEN_PIPE_PIPE
		|| n == TOKEN_AND_AND || n == TOKEN_END)
		return (1);
	return (0);
}
