/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:09:23 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/07 12:14:15 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_redirect(token_t *token, lexer_t *lexer)
{
	if (token->type == TOKEN_OLD_THAN)
	{
		free_if_exists(data.cmds[data.index].output);
		data.cmds[data.index].output = parser_handle_dollar_sign(
				parser_expect(lexer, TOKEN_WORD).value, 1);
		data.append = 0;
		if (!data.err)
			open(data.cmds[data.index].output, O_RDWR | O_CREAT, 0644);
	}
	else if (token->type == TOKEN_GREAT_GREAT)
	{
		data.append = 1;
		free_if_exists(data.cmds[data.index].output);
		data.cmds[data.index].output = parser_handle_dollar_sign(
			parser_expect(lexer, TOKEN_WORD).value, 1);
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
	char	*str;

	if (ft_strchr(token->value, ASTERISK))
		parser_check_asterisk(token);
	else
	{
		str = parser_handle_dollar_sign(token->value, 1);
		if (is_empty_string(str))
		{
			free(str);
			str = lexer_get_char_as_string(-2);
		}
		data.cmds[data.index].str = join_with_sep(
				data.cmds[data.index].str, str, -1);
	}
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*new;

	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == SINGLE_QUOTES || str[i] == DOUBLE_QUOTES))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	return (new);
}

void	parser_handle_heredoc(lexer_t *lexer)
{
	char	*tmp;

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

int	is_commands_breaker(int n)
{
	if (n == TOKEN_PIPE || n == TOKEN_PIPE_PIPE
		|| n == TOKEN_AND_AND || n == TOKEN_END)
		return (1);
	return (0);
}
