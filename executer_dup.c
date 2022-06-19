/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:50:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/19 14:28:07 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_input_files(int cmd_idx)
{
	int		i;
	char	**inputs;

	inputs = ft_split(g_data.cmds[cmd_idx].input, -1);
	i = 0;
	while (inputs && inputs[i])
	{
		if (access(inputs[i], F_OK | R_OK) == -1)
		{
			perror("minishell");
			g_data.cmds[cmd_idx].err = 1;
			g_data.exit_code = 1;
			i++;
			break ;
		}
		i++;
	}
	free_if_exists(g_data.cmds[cmd_idx].input);
	if (inputs)
		g_data.cmds[cmd_idx].input = ft_strdup(inputs[i - 1]);
	free_arr(inputs);
}

void	check_output_files(int cmd_idx)
{
	int		i;
	char	**outputs;

	outputs = ft_split(g_data.cmds[cmd_idx].output, -1);
	i = 0;
	while (outputs && outputs[i])
	{
		if (open(outputs[i], O_CREAT, 0644) == -1)
		{
			perror("minishell");
			g_data.cmds[cmd_idx].err = 1;
			g_data.exit_code = 1;
			i++;
			break ;
		}
		i++;
	}
	free_if_exists(g_data.cmds[cmd_idx].output);
	if (outputs && outputs[0])
		g_data.cmds[cmd_idx].output = ft_strdup(outputs[i - 1]);
	else if (outputs)
		g_data.cmds[cmd_idx].output = ft_strdup("");
	free_arr(outputs);
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
			exit(ERROR);
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
		if (g_data.cmds[i].output[0] == '\0')
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			exit(ERROR);
		}
		if (g_data.cmds[i].append)
			fd = open(g_data.cmds[i].output, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(g_data.cmds[i].output, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			exit(ERROR);
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
		if (g_data.cmds[i].append)
			fd = open(g_data.cmds[i].output, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(g_data.cmds[i].output, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			exit(FAILURE);
		dup2(fd, STDOUT);
	}
}
