/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:46:47 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/08 20:17:32 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_form_stdout(char *limit, int fd)
{
	char	*line;

	line = get_next_line(STD);
	while (ft_strncmp(limit, line, ft_strlen(limit)))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
}

void	close_unused_pipes(t_cmd *cmd, int process_index, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i != process_index - 1)
			close(cmd[i].p[STDIN]);
		if (i != process_index)
			close(cmd[i].p[STDOUT]);
		i++;
	}
}

void	close_all_pipes(t_cmd *cmd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(cmd[i].p[STDIN]);
		close(cmd[i].p[STDOUT]);
		i++;
	}
}

void	wait_all_child_processors(t_cmd *cmd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(cmd[i].pid, 0, 0);
		i++;
	}
}

void	get_path(t_cmd *cmd, char **arr, char *command, int i)
{
	int		j;
	int		a;
	char	*path;

	if (!arr)
		return ;
	j = 0;
	while (arr[j])
	{
		cmd[i].path = NULL;
		path = ft_strjoin(arr[j], command);
		a = access(path, F_OK);
		if (a == 0)
		{
			cmd[i].path = path;
			break ;
		}
		free(path);
		j++;
	}
}
