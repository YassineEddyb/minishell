/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:26:02 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/01 11:57:18 by yed-dyb          ###   ########.fr       */
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
		if (data.heredoc == 1)
		{
			str = ft_substr(line, 0, ft_strlen(line) - 1);
			free(line);
			line = join_and_free(parser_handle_dollar_sign(str, 0), ft_strdup("\n"));
			free(str);
		}
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN);
	}
	free(line);
}

void	here_doc(void)
{
	int	fd;

	data.limit = join_and_free(data.limit, ft_strdup("\n"));
	fd = open("/tmp/.temp", O_RDWR | O_CREAT | O_TRUNC, 0664);
	read_form_stdout(data.limit, fd);
	free_if_exists(data.limit);
	close(fd);
}
