/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path_and_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:32:47 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/05 11:40:08 by yed-dyb          ###   ########.fr       */
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
			data.cmds[i].path = path;
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

	arr = ft_split(getenv("PATH"), ':');
	i = 0;
	while (i < data.num_of_cmds)
	{
		if (data.cmds[i].str)
		{
			pipe(data.cmds[i].p);
			command = ft_strjoin("/", data.cmds[i].args[0]);
			check_for_path(arr, command, i);
			free(command);
		}
		i++;
	}
	free_arr(arr);
}

static void	get_args(void)
{
	int	i;
	int j;

	i = 0;
	while (i < data.num_of_cmds)
	{
		if (!data.cmds[i].path)
			data.cmds[i].args = ft_split(data.cmds[i].str, -1);
		i++;
	}
	i = 0;
	while (i < data.num_of_cmds)
	{
		j = 0;
		while(data.cmds[i].args && data.cmds[i].args[j])
		{
			if (data.cmds[i].args[j][0] == -2)
			{
				free(data.cmds[i].args[j]);
				data.cmds[i].args[j] = ft_strdup("");
			}
			j++;
		}
		i++;
	}
}

static void replace_args(void)
{
	int i;
	int j;

	while (i < data.num_of_cmds)
	{
		if (!data.cmds[i].path)
			data.cmds[i].args = ft_split(data.cmds[i].str, -1);
		i++;
	}
}

void	get_path_and_args(void)
{
	if (!data.err)
	{
		get_args();
		get_path();
	}
}
