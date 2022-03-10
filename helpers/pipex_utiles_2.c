/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utiles_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:37:10 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/02/21 15:13:34 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_input(t_data *data, t_cmd *cmd, int i)
{
	int	fd;

	if (compare_strings(data->input, "here_doc"))
		fd = open("/tmp/.temp", O_RDONLY, 0664);
	else
	{
		fd = open(data->input, O_RDONLY, 0664);
		if (fd < 0)
		{
			perror("./pipex");
			exit(1);
		}
	}
	dup2(fd, 0);
	dup2(cmd[i].p[1], 1);
}

int	compare_strings(char *s1, char *s2)
{
	int	len;

	if (ft_strlen(s1) > ft_strlen(s2))
		len = ft_strlen(s1);
	else
		len = ft_strlen(s2);
	if (!ft_strncmp(s1, s2, len))
		return (1);
	return (0);
}

void	check_path(t_cmd *cmd, int i)
{
	if (!cmd[i].path)
	{
		if (ft_strchr(cmd[i].args[0], '/'))
			cmd[i].path = cmd[i].args[0];
		else
		{
			ft_putstr_fd("./pipex: command not found\n", 2);
			exit(1);
		}
	}
}

int	look_for_paths_index(char **env)
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

void	get_args(t_cmd *cmd, char **av, int i)
{
	int	j;

	j = 0;
	if (ft_strchr(av[i], '\''))
	{
		ft_replace(ft_strchr(av[i], '\''), ' ', -1);
		cmd[i].args = ft_split(av[i], ' ');
		while (cmd[i].args[j])
		{
			if (cmd[i].args[j][0] == '\'')
			{
				ft_replace(cmd[i].args[j], -1, ' ');
				cmd[i].args[j] = ft_substr(cmd[i].args[j], 1, \
					ft_strlen(cmd[i].args[j]) - 2);
			}
			j++;
		}
	}
	else
		cmd[i].args = ft_split(av[i], ' ');
}
