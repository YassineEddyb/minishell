/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   executer.c										 :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: yed-dyb <yed-dyb@student.42.fr>			+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2022/03/14 21:08:29 by yed-dyb		   #+#	#+#			      */
/*   Updated: 2022/06/05 13:36:09 by yed-dyb		  ###   ########.fr	      */
/*																		      */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_cmd(char *cmd)
{
	int		i;
	char	**cmds;

	cmds = ft_split("cd echo export exit pwd env", ' ');
	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(cmd, cmds[i], ft_strlen(cmd) + 1))
		{
			free_arr(cmds);
			return (1);
		}
		i++;
	}
	free_arr(cmds);
	return (0);
}

int	is_builtin(int i)
{
	if (g_data.num_of_cmds > 1)
		return (0);
	dup_output_file(i);
	if (!ft_strncmp(g_data.cmds[i].args[0], "echo", 5))
		echo_cmd(g_data.cmds[i].args);
	else if (!ft_strncmp(g_data.cmds[i].args[0], "pwd", 4))
		pwd_cmd();
	else if (!ft_strncmp(g_data.cmds[i].args[0], "env", 4))
		env_cmd(g_data.cmds[i].args);
	else if (!ft_strncmp(g_data.cmds[i].args[0], "cd", 3))
		cd_cmd(g_data.cmds[i].args);
	else if (!ft_strncmp(g_data.cmds[i].args[0], "export", 7))
		export_cmd(g_data.cmds[i].args);
	else if (!ft_strncmp(g_data.cmds[i].args[0], "unset", 6))
		unset_cmd(g_data.cmds[i].args, 0);
	else if (!ft_strncmp(g_data.cmds[i].args[0], "exit", 5))
		exit_cmd(g_data.cmds[i].args);
	if (is_builtin_cmd(g_data.cmds[i].args[0]))
		dup2(0, 1);
	return (is_builtin_cmd(g_data.cmds[i].args[0]));
}

void	execute_commands(void)
{
	int	i;

	i = -1;
	while (++i < g_data.num_of_cmds)
	{
		if (g_data.cmds[i].args && !is_builtin(i))
		{
			g_data.cmds[i].pid = fork();
			if (i < g_data.num_of_cmds && g_data.cmds[i].pid == 0)
			{
				close_unused_pipes(i);
				dup_all(i);
				if (!is_builtin(i))
				{
					check_is_path(i);
					if (execve(g_data.cmds[i].path, g_data.cmds[i].args, g_data.env))
						perror("minishell");
					exit(ERROR);
				}
				exit(g_data.exit_code);
			}
		}
		if (i < g_data.num_of_cmds && !handle_and_and_or(i))
			break ;
	}
}

void	execute(void)
{
	if (!g_data.err)
	{
		execute_commands();
		close_all_pipes();
		wait_all_child_processors();
	}
}
