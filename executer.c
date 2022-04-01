/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:08:29 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/04/01 12:03:32 by yed-dyb          ###   ########.fr       */
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
    if (data.cmds[i].output)
    {
        if (data.append || data.heredoc)
            fd = open(data.cmds[i].output, O_RDWR | O_CREAT | O_APPEND, 0664);
        else
            fd = open(data.cmds[i].output, O_CREAT | O_WRONLY | O_TRUNC, 0664);
        if (fd == -1)
        {
            perror("minishell");
            exit(FAILURE);
        }
        dup2(fd, STDOUT);
    }
    if (i == data.num_of_cmds - 1)
    {
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

void handle_sigint(int sig)
{
    data.exit_code = 130;
    // exit(ERROR);
}

int is_builtin(int i)
{
    if (!ft_strncmp(data.cmds[i].args[0], "echo", 5))
        echo_cmd(data.cmds[i].args);
	return 0;
}

void    execute_commands()
{
    int     i;
    struct sigaction sa;
	sa.sa_handler = &handle_sigint;

    i = 0;
    while (i < data.num_of_cmds)
    {
        data.cmds[i].pid = fork();
        if (!ft_strncmp(data.cmds[i].args[0], "cd", 3))
            cd_cmd(data.cmds[i].args);
        else if (data.cmds[i].pid == 0)
        {
            sigaction(SIGINT, &sa, NULL);
            close_unused_pipes(i);
            dup_all(i);
            check_is_path(i);
			//printf("%s\n", data.cmds[i].args[0]);
            if (!is_builtin(i))
			{
				if (execve(data.cmds[i].path, data.cmds[i].args, data.env) == -1)
					perror("minishell");
			}
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