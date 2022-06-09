/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:09:23 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/08 19:34:49 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_redirect(t_token *token, t_lexer *lexer)
{
	if (token->e_type == TOKEN_OLD_THAN)
	{
		free_if_exists(g_data.cmds[g_data.index].output);
		g_data.cmds[g_data.index].output = parser_handle_dollar_sign(
				parser_expect(lexer, TOKEN_WORD).value);
		g_data.append = 0;
		open_file(g_data.cmds[g_data.index].output);
	}
	else if (token->e_type == TOKEN_GREAT_GREAT)
	{
		g_data.append = 1;
		free_if_exists(g_data.cmds[g_data.index].output);
		g_data.cmds[g_data.index].output = parser_handle_dollar_sign(
				parser_expect(lexer, TOKEN_WORD).value);
		open_file(g_data.cmds[g_data.index].output);
	}
	else if (token->e_type == TOKEN_PIPE_PIPE)
		g_data.cmds[g_data.index].or = 1;
	else if (token->e_type == TOKEN_AND_AND)
		g_data.cmds[g_data.index].and = 1;
	else if (token->e_type == TOKEN_PIPE)
		g_data.cmds[g_data.index].pipe = 1;
	if (token->e_type == TOKEN_AND_AND || token->e_type == TOKEN_PIPE
		||token->e_type == TOKEN_PIPE_PIPE)
		g_data.index++;
}

void	parser_handle_word(t_token *token)
{
	char	*str;

	if (ft_strchr(token->value, ASTERISK))
		parser_check_asterisk(token);
	else
	{
		str = parser_handle_dollar_sign(token->value);
		if (is_empty_string(str))
		{
			free(str);
			str = lexer_get_char_as_string(-2);
		}
		g_data.cmds[g_data.index].str = join_with_sep(
				g_data.cmds[g_data.index].str, str, -1);
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

void	parser_handle_heredoc(t_lexer *lexer)
{
	char	*tmp;

	tmp = parser_expect(lexer, TOKEN_WORD).value;
	if (ft_strchr(tmp, DOUBLE_QUOTES) || ft_strchr(tmp, SINGLE_QUOTES))
		g_data.heredoc = 2;
	else
		g_data.heredoc = 1;
	g_data.limit = remove_quotes(tmp);
	free(tmp);
	here_doc();
	free_if_exists(g_data.cmds[g_data.index].input);
}

int	is_commands_breaker(int n)
{
	if (n == TOKEN_PIPE || n == TOKEN_PIPE_PIPE
		|| n == TOKEN_AND_AND || n == TOKEN_END)
		return (1);
	return (0);
}
