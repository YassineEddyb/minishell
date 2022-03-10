/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:54 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/10 10:54:45 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(t_data *data, int i, char c)
{
	int j;

	j = 0;
	while (data->cmds[i].args[j])
	{
		if (data->cmds[i].args[j][0] == c)
		{
			ft_replace(data->cmds[i].args[j], -1, SPACE, c);
			data->cmds[i].args[j] = ft_substr(data->cmds[i].args[j], 1, \
				ft_strlen(data->cmds[i].args[j]) - 2);
		}
		j++;
	}
}

void remove_redirections(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
	{
		if (ft_strchr(arr[i], LESS_THAN))
			arr[i] = ft_split(arr[i], LESS_THAN)[0];
		if (ft_strchr(arr[i], OLD_THAN))
			arr[i] = ft_split(arr[i], OLD_THAN)[0];
		i++;
	}
}

void get_args(t_data *data, char *str)
{
	int i;
	char **arr;

	arr = ft_split(str, '|');
	remove_redirections(arr);
	i = 0;
	while(arr[i])
	{
		data->cmds[i].args = ft_split(arr[i], SPACE);
		handle_quotes(data, i, SINGLE_QUOTES);
		handle_quotes(data, i, DOUBLE_QUOTES);
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
		pipe(data->cmds[i].p);
		command = ft_strjoin("/", data->cmds[i].args[0]);
		check_for_path(data, arr, command, i);
		free(command);
		i++;
	}
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
	str = trim_spaces(str);
	fill_quotes(str, SINGLE_QUOTES);
	fill_quotes(str, DOUBLE_QUOTES);
	check_input_output(data, str);
	get_args(data, str);
	get_path(data, arr);
}