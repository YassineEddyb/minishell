/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:50:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/14 21:44:51 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_input_files(void)
{
	int	i;
	int	j;
	char **inputs;

	i = 0;
	j = 0;
	while (i < g_data.num_of_cmds)
	{
		inputs = ft_split(g_data.cmds[i].input, -1);
		j = 0;
		while (inputs && inputs[j])
		{
			if (access(inputs[j], F_OK | R_OK) == -1)
			{
				perror("minshell");
				g_data.cmds[i].err = 1;
				break ;
				g_data.exit_code = 1;
			}
			j++;
		}
		if (inputs && !g_data.cmds[i].heredoc)
		{
			free_if_exists(g_data.cmds[i].input);
			g_data.cmds[i].input = inputs[j - 1];
		}
		i++;
	}
}

void check_output_files(int cmd_idx)
{
	int	i;
	char **outputs;

	outputs = ft_split(g_data.cmds[cmd_idx].output, -1);
	i = 0;
	while (outputs && outputs[i])
	{
		if (open(outputs[i], O_CREAT, 0644) == -1)
		{
			perror("minshell");
			g_data.cmds[cmd_idx].err = 1;
			break ;
			g_data.exit_code = 1;
		}
		i++;
	}
	if (outputs)
	{
		free_if_exists(g_data.cmds[cmd_idx].output);
		g_data.cmds[cmd_idx].output = outputs[i - 1];
	}
}


static void	handle_input(int i)
{
	int	fd;

	if (g_data.cmds[i].heredoc)
		dup2(g_data.cmds[i].doc[0], STDIN);
	else if (g_data.cmds[i].input)
	{
		fd = open(g_data.cmds[i].input, O_RDONLY, 0644);
		if (fd == -1)
			exit(FAILURE);
		dup2(fd, STDIN);
	}
	else if (i > 0 && g_data.cmds[i - 1].pipe)
		dup2(g_data.cmds[i - 1].p[STDIN], STDIN);
}

void	dup_all(int i)
{
	int	fd; 

	handle_input(i);
	if (g_data.cmds[i].output)
	{
		check_output_files(i);
		if (g_data.cmds[i].append )
			fd = open(g_data.cmds[i].output, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(g_data.cmds[i].output, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("minishell");
			exit(FAILURE);
		}
		dup2(fd, STDOUT);
		close(fd);
	}
	else if (g_data.cmds[i].pipe)
		dup2(g_data.cmds[i].p[STDOUT], STDOUT);
}

void	dup_output_file(int i)
{
	int	fd;

	if (g_data.cmds[i].output && is_builtin_cmd(g_data.cmds[i].args[0]))
	{
		check_output_files(i);
		if (g_data.cmds[i].append)
			fd = open(g_data.cmds[i].output, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(g_data.cmds[i].output, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("minishell");
			exit(FAILURE);
		}
		dup2(fd, STDOUT);
	}
}
