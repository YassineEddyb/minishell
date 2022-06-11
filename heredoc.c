/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:26:02 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/11 21:29:03 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_form_stdout(char *limit, int fd)
{
	char	*line;
	char	*str;

	line = readline("heredoc> ");
	while (line && ft_strncmp(limit, line, ft_strlen(limit)))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
}

void	here_doc(void)
{
	pipe(g_data.cmds[g_data.index].doc);
	g_data.heredoc_signal = 1;
	read_form_stdout(g_data.limit, g_data.cmds[g_data.index].doc[1]);
	g_data.heredoc_signal = 0;
	close(g_data.cmds[g_data.index].doc[1]);
	free_if_exists(g_data.limit);
	close(0);
	dup(g_data.fd);
}
