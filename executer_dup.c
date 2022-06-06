/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:50:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/06 14:52:24 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_input(int i)
{
	int	fd;

	if (data.heredoc)
	{
		fd = open("/tmp/.temp", O_RDONLY, 0644);
		dup2(fd, STDIN);
	}
	else if (data.cmds[i].input)
	{
		fd = open(data.cmds[i].input,  O_RDONLY, 0644);
		if (fd == -1)
		{
			perror("minishell");
			exit(FAILURE);
		}
		dup2(fd, STDIN);
	}
	else if (i > 0 && data.cmds[i - 1].pipe)
		dup2(data.cmds[i - 1].p[STDIN], STDIN);
}

void	dup_all(int i)
{
	int	 fd;

	handle_input(i);
	if (data.cmds[i].output)
	{
		if (data.append)
			fd = open(data.cmds[i].output, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			fd = open(data.cmds[i].output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("minishell");
			exit(FAILURE);
		}
		dup2(fd, STDOUT);
	} else if (data.cmds[i].pipe)
		dup2(data.cmds[i].p[STDOUT], STDOUT);
}

void dup_output_file(int i)
{
    int fd;

    if (data.cmds[i].output && is_builtin_cmd(data.cmds[i].args[0]))
	{
		if (data.append)
			fd = open(data.cmds[i].output, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			fd = open(data.cmds[i].output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("minishell");
			exit(FAILURE);
		}
		dup2(fd, STDOUT);
	} 
}