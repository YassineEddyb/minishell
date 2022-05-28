/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:25:37 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/28 12:36:55 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_unused_pipes(int process_index)
{
	int	i;

	i = 0;
	while (i < data.num_of_cmds)
	{
		if (i != process_index - 1)
			close(data.cmds[i].p[STDIN]);
		if (i != process_index)
			close(data.cmds[i].p[STDOUT]);
		i++;
	}
}

void	close_all_pipes()
{
	int	i;

	i = 0;
	while (i < data.num_of_cmds)
	{
		close(data.cmds[i].p[STDIN]);
		close(data.cmds[i].p[STDOUT]);
		i++;
	}
}

void	wait_all_child_processors()
{
	int	i;
	int status;

	i = 0;
	while (i < data.num_of_cmds)
	{
		waitpid(data.cmds[i].pid, &status, 0);
		if (WIFEXITED(status))
			data.exit_code = WEXITSTATUS(status);
		else 
			data.exit_code = 130;
		i++;
	}
}

void	check_is_path(int i)
{
	if (!data.cmds[i].path)
	{
		if (ft_strchr(data.cmds[i].args[0], '/'))
			data.cmds[i].path = data.cmds[i].args[0];
		else
		{
			ft_putstr_fd("minishell: command not found: ", STDERR);
            ft_putstr_fd(data.cmds[i].args[0], STDERR);
            ft_putstr_fd("\n", STDERR);
			exit(127);
		}
	}
}