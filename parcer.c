/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:54 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/08 13:41:42 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_num_of_cmds(char *str)
{
	int i;
	int len;

	i = 0;
	len = 1;
	while(str[i])
	{
		if (str[i] == '|')
			len++;
		i++;
	}
	return len;
}

void get_args(t_data *data, char *str)
{
	int i;
	char **arr;

	arr = ft_split(str, '|');
	i = 0;
	while(arr[i])
	{
		data->cmds[i].args = ft_split(arr[i], ' ');
		i++;
	}
}

void    check_for_path(t_data *data, char **arr, char *command, int i)
{
	int		j;
	int		a;
	char	*path;

	if (!arr)
		return ;
	j = 0;
	while (arr[j])
	{
		data->cmds[i].path = NULL;
		path = ft_strjoin(arr[j], command);
		a = access(path, F_OK);
		if (a == 0)
		{
			data->cmds[i].path = path;
			break ;
		}
		free(path);
		j++;
	}
}

void    get_path(t_data *data, char **arr)
{
	int		i;
	char	*command;

	i = 0;
	while (i < data->num_of_cmds)
	{
		//pipe(cmd[i].p);
		command = ft_strjoin("/", data->cmds[i].args[0]);
		check_for_path(data, arr, command, i);
		free(command);
		i++;
	}
}

int     look_for_paths_index(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	return (i);
}

void parce(t_data *data, char *str, char **env)
{
	char **arr;
	char *s;
	s = ft_substr(env[look_for_paths_index(env)], 5, ft_strlen(env[6]));
    arr = ft_split(s, ':');
    free(s);
	data->num_of_cmds = get_num_of_cmds(str);
	data->cmds = malloc(data->num_of_cmds * sizeof(t_cmd));
	get_args(data, str);
	get_path(data, arr);
}