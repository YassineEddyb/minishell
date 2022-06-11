/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:26:02 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/11 17:56:41 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_form_stdout(char *limit, int fd)
{
	char	*line;
	char	*str;

	write(1, "heredoc> ", 9);
	line = get_next_line(STDIN);
	while (line && ft_strncmp(limit, line, ft_strlen(limit)))
	{
		write(1, "heredoc> ", 9);
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN);
	}
	free(line);
}

void	here_doc(void)
{
	pipe(g_data.cmds[g_data.index].doc);
	g_data.limit = join_and_free(g_data.limit, ft_strdup("\n"));
	read_form_stdout(g_data.limit, g_data.cmds[g_data.index].doc[1]);
	close(g_data.cmds[g_data.index].doc[1]);
	free_if_exists(g_data.limit);
}
