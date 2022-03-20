/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:08:29 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/19 20:09:14 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input(int i)
{
	int	fd;

	if (data.heredoc)
    {
		fd = open("/tmp/.temp", O_RDONLY, 0664);
        dup2(fd, STDIN);
    }
    if (data.input)
    {
        fd = open(data.input,  O_RDONLY, 0644);
        if (fd == -1)
        {
            perror("minishell");
            exit(FAILURE);
        }
        dup2(fd, STDIN);
    }
    if (data.num_of_cmds >= 2)
        dup2(data.cmds[i].p[STDOUT], STDOUT);
}

void    dup_all(int i)
{
    int     fd;

    if (i == 0)
    {
        handle_input(i);
    }
    if (i == data.num_of_cmds - 1)
    {
        if (data.output)
        {
            if (data.append || data.heredoc)
                fd = open(data.output, O_RDWR | O_CREAT | O_APPEND, 0664);
            else
                fd = open(data.output, O_CREAT | O_WRONLY | O_TRUNC, 0664);
            if (fd == -1)
            {
                perror("minishell");
                exit(FAILURE);
            }
            dup2(fd, STDOUT);
        }
        if (i > 0)
            dup2(data.cmds[i - 1].p[STDIN], STDIN);
        close(data.cmds[i].p[STDOUT]);
    }
    if (i > 0 && i < data.num_of_cmds - 1)
    {
        dup2(data.cmds[i - 1].p[STDIN], STDIN);
        dup2(data.cmds[i].p[STDOUT], STDOUT);
    }
}

void    execute_commands()
{
    int     i;

    i = 0;
    while (i < data.num_of_cmds)
    {
        data.cmds[i].pid = fork();
        if (data.cmds[i].pid == 0)
        {
            close_unused_pipes(i);
            dup_all(i);
            check_path(i);
            if (execve(data.cmds[i].path, data.cmds[i].args, data.env) == -1)
                perror("minishell");
            exit(ERROR);
        }
        i++;
    }
}

void execute()
{
    if (!data.err)
    {
        if (data.heredoc)
            here_doc();
        execute_commands();
        close_all_pipes();
        wait_all_child_processors();
    }
}