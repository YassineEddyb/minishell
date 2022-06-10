/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:25:37 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/09 13:57:16 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_unused_pipes(int process_index)
{
	int	i;

	i = 0;
	while (i < g_data.num_of_cmds)
	{
		if (i != process_index - 1)
			close(g_data.cmds[i].p[STDIN]);
		if (i != process_index)
			close(g_data.cmds[i].p[STDOUT]);
		i++;
	}
}

void	close_all_pipes(void)
{
	int	i;

	i = 0;
	while (i < g_data.num_of_cmds)
	{
		close(g_data.cmds[i].p[STDIN]);
		close(g_data.cmds[i].p[STDOUT]);
		i++;
	}
}

void	wait_all_child_processors(void)
{
	int	i;
	int	status;

	i = 0;
	while (i < g_data.num_of_cmds)
	{
		if (g_data.cmds[i].args && (!is_builtin_cmd(g_data.cmds[i].args[0]) || g_data.num_of_cmds > 1))
		{
			waitpid(g_data.cmds[i].pid, &status, 0);
			if (WIFEXITED(status))
				g_data.exit_code = WEXITSTATUS(status);
			else
				g_data.exit_code = 130;
		}
		i++;
	}
}

void	check_is_path(int i)
{
	if (!g_data.cmds[i].path)
	{
		if (g_data.cmds[i].args[0] != '\0' && ft_strchr(
				g_data.cmds[i].args[0], '/'))
			g_data.cmds[i].path = g_data.cmds[i].args[0];
		else
		{
			ft_putstr_fd("minishell: command not found: ", STDERR);
			ft_putstr_fd(g_data.cmds[i].args[0], STDERR);
			ft_putstr_fd("\n", STDERR);
			exit(127);
		}
	}
}
