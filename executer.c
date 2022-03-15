/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:08:29 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/14 21:09:07 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    dup_all(t_data *data, int i)
{
    int     fd;

    if (i == 0)
    {
        if (data->input)
        {
            fd = open(data->input,  O_RDONLY, 0644);
            if (fd == -1)
                printf("Error opening input file\n");
            dup2(fd, STDIN);
        }
        if (data->num_of_cmds >= 2)
            dup2(data->cmds[i].p[STDOUT], STDOUT);
    }
    if (i == data->num_of_cmds - 1)
    {
        // if (!compare_strings(data->input, "here_doc"))
        //         fd = open(data->output, O_CREAT | O_RDWR | O_TRUNC, 0664);
        // else
        //         fd = open(data->output, O_RDWR | O_CREAT | O_APPEND, 0664);
        // if (fd < 0)
        // {
        //         perror("./pipex");
        //         exit(1);
        // }

        if (data->output)
        {
            fd = open(data->output, O_CREAT | O_WRONLY | O_TRUNC, 0664);
            if (fd == -1)
                printf("Error opening output file\n");
            dup2(fd, STDOUT);
        }
        if (i > 0)
            dup2(data->cmds[i - 1].p[STDIN], STDIN);
        close(data->cmds[i].p[STDOUT]);
    }
    if (i > 0 && i < data->num_of_cmds - 1)
    {
        dup2(data->cmds[i - 1].p[STDIN], STDIN);
        dup2(data->cmds[i].p[STDOUT], STDOUT);
    }
}

void	close_unused_pipes(t_data *data, int process_index)
{
	int	i;

	i = 0;
	while (i < data->num_of_cmds)
	{
		if (i != process_index - 1)
			close(data->cmds[i].p[STDIN]);
		if (i != process_index)
			close(data->cmds[i].p[STDOUT]);
		i++;
	}
}

void	close_all_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_cmds)
	{
		close(data->cmds[i].p[STDIN]);
		close(data->cmds[i].p[STDOUT]);
		i++;
	}
}

void	wait_all_child_processors(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_cmds)
	{
		waitpid(data->cmds[i].pid, 0, 0);
		i++;
	}
}

void    execute_commands(t_data *data, char **env)
{
    int     i;

    i = 0;
    while (i < data->num_of_cmds)
    {
        data->cmds[i].pid = fork();
        if (data->cmds[i].pid == 0)
        {
            close_unused_pipes(data, i);
            dup_all(data, i);
            //check_path(cmd, i);
            if (execve(data->cmds[i].path, data->cmds[i].args, env) == -1)
                    perror("minishell");
            exit(1);
        }
        i++;
    }
}

// void    here_doc(t_data *data, char **av)
// {
//         int     fd;

//         if (compare_strings(data->input, "here_doc"))
//         {
//                 data->limit = ft_strjoin(av[2], "\n");
//                 fd = open("/tmp/.temp", O_RDWR | O_CREAT | O_TRUNC, 0664);
//                 read_form_stdout(data->limit, fd);
//                 free(data->limit);
//                 close(fd);
//         }
// }

void execute(t_data *data, char **env)
{
    execute_commands(data, env);
    close_all_pipes(data);
    wait_all_child_processors(data);
}