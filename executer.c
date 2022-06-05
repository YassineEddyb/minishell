/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:08:29 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/05 13:36:09 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input(int i)
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

void    dup_all(int i)
{
    int     fd;

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

int is_builtin_cmd(char *cmd)
{
    int i = 0;
    char *cmds[6] = {"echo", "env", "export", "unset", "pwd", "cd"};

    
    while(i < 6)
    {
        if (!ft_strncmp(cmd, cmds[i], ft_strlen(cmd) + 1))
            return (1);
        i++;
    }
    return (0);
}

int is_builtin(int i)
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
    if (data.cmds[i].pipe)
        return (0);
    if (!ft_strncmp(data.cmds[i].args[0], "echo", 5))
        echo_cmd(data.cmds[i].args);
    else if (!ft_strncmp(data.cmds[i].args[0], "pwd", 4))
        pwd_cmd();
    else if (!ft_strncmp(data.cmds[i].args[0], "env", 4))
        env_cmd(data.cmds[i].args);
    else if (!ft_strncmp(data.cmds[i].args[0], "cd", 3)) 
        cd_cmd(data.cmds[i].args);
    else if (!ft_strncmp(data.cmds[i].args[0], "export", 7))
        export_cmd(data.cmds[i].args);
    else if (!ft_strncmp(data.cmds[i].args[0], "unset", 6))
        unset_cmd(data.cmds[i].args);
    else if (!ft_strncmp(data.cmds[i].args[0], "exit", 5)) 
        exit_cmd(data.cmds[i].args);

    if (is_builtin_cmd(data.cmds[i].args[0]))
        dup2(0, 1);
    return (is_builtin_cmd(data.cmds[i].args[0]));
}

void    execute_commands()
{
    int     i;

    i = 0;
    while (i < data.num_of_cmds)
    {
        if (data.cmds[i].args)
        {
            if (!is_builtin(i))
            {
                data.cmds[i].pid = fork();
                if (i < data.num_of_cmds && data.cmds[i].pid == 0)
                {
                    close_unused_pipes(i);
                    dup_all(i);
                    if (!is_builtin(i))
                    {
                        check_is_path(i);
                        if (execve(data.cmds[i].path, data.cmds[i].args, data.env) == -1)
                            perror("minishell");
                        exit(ERROR);
                    }
                    exit(data.exit_code);
                }
            }
        }
        if (i < data.num_of_cmds && !handle_and_and_or(i))
            break ;
        i++;
    }
}

void execute()
{
    if (!data.err)
    {
        execute_commands();
        close_all_pipes();
        wait_all_child_processors();
    }
}