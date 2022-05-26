/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:26:02 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/26 13:13:29 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_form_stdout(char *limit, int fd)
{
	char	*line;

	write(1, "heredoc> ", 9);
	line = get_next_line(STDIN);
	while (ft_strncmp(limit, line, ft_strlen(limit)))
	{
		write(1, "heredoc> ", 9);
		line = ft_strjoin(parser_handle_string(ft_substr(line,0, ft_strlen(line) - 1)), "\n");
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN);
	}
	free(line);
}

void	here_doc(void)
{
	int	fd;

	data.limit = ft_strjoin(data.limit, "\n");
	fd = open("/tmp/.temp", O_RDWR | O_CREAT | O_TRUNC, 0664);
	read_form_stdout(data.limit, fd);
	free(data.limit);
	close(fd);
}
