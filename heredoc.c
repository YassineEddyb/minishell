/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:26:02 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/18 10:26:50 by yed-dyb          ###   ########.fr       */
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
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN);
	}
	free(line);
}

void    here_doc()
{
    int     fd;

    data.limit = ft_strjoin(data.limit, "\n");
    fd = open("/tmp/.temp", O_RDWR | O_CREAT | O_TRUNC, 0664);
    read_form_stdout(data.limit, fd);
    free(data.limit);
    close(fd);
}
