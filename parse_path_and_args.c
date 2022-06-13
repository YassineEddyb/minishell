/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path_and_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:32:47 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/13 11:54:47 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_for_path(char **arr, char *command, int i)
{
	int		j;
	int		a;
	char	*path;

	if (!arr)
		return ;
	j = 0;
	while (arr[j])
	{
		path = ft_strjoin(arr[j], command);
		a = access(path, F_OK);
		if (a == 0)
		{
			g_data.cmds[i].path = path;
			break ;
		}
		free(path);
		j++;
	}
}

static void	get_path(void)
{
	int		i;
	char	*command;
	char	**arr;
	char	*tmp;

	tmp = get_env_variable("PATH");
	arr = ft_split(tmp, ':');
	i = 0;
	while (i < g_data.num_of_cmds)
	{
		pipe(g_data.cmds[i].p);
		if (g_data.cmds[i].str)
		{
			command = ft_strjoin("/", g_data.cmds[i].args[0]);
			check_for_path(arr, command, i);
			free(command);
		}
		i++;
	}
	free_if_exists(tmp);
	free_arr(arr);
}

static void	get_args(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_data.num_of_cmds)
	{
		if (!g_data.cmds[i].path)
			g_data.cmds[i].args = ft_split(g_data.cmds[i].str, -1);
		i++;
	}
	i = 0;
	while (i < g_data.num_of_cmds)
	{
		j = 0;
		while (g_data.cmds[i].args && g_data.cmds[i].args[j])
		{
			if (g_data.cmds[i].args[j][0] == -2)
			{
				free(g_data.cmds[i].args[j]);
				g_data.cmds[i].args[j] = ft_strdup("");
			}
			j++;
		}
		i++;
	}
}

void	get_path_and_args(void)
{
	if (!g_data.err)
	{
		get_args();
		get_path();
	}
}
