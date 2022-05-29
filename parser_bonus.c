/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 12:03:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/29 16:41:11 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_match(char *str, char *match)
{
	if (!*str && !*match)
		return (1);
	if (!*str && *match == ASTERISK)
		return (is_match(str, match + 1));
	if (!*str || !*match)
		return (0);
	if (*str == *match)
		return (is_match(str + 1, match + 1));
	if (*match == ASTERISK)
		return (is_match(str + 1, match) || 
			is_match(str, match + 1));
	return (0);
}

void	parser_check_asterisk(token_t *token)
{
	int				i;
	struct dirent	*de;
	DIR				*dr;

	dr = opendir(".");
	i = 0;
	de = readdir(dr);
	while (de != NULL)
	{
		if (is_match(de->d_name, token->value) && de->d_name[0] != '.')
		{
			data.cmds[data.index].str
				= join_with_sep(data.cmds[data.index].str, de->d_name, -1);
			i++;
		}
		de = readdir(dr);
	}
	closedir(dr);
	if (i == 0)
	{
		data.cmds[data.index].str = join_with_sep(
				data.cmds[data.index].str, parser_handle_dollar_sign(token->value, 1), -1);
	}
}
