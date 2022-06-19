/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:24:18 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/18 19:19:12 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_path(char **env, char *path)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], path, ft_strlen_till_c(env[i], '=')))
			return (ft_substr(env[i],
					ft_strlen_till_c(env[i], '=') + 1, ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}

void	cd2(char **args)
{
	if (ft_strncmp(args[1], ".", ft_strlen(args[1])) == 0)
	{
		chdir((const char *)".");
		g_data.exit_code = 0;
	}
	else if (ft_strncmp(args[1], "..", ft_strlen(args[1])) == 0)
	{
		chdir("..");
		g_data.exit_code = 0;
	}
	else
	{
		if (chdir(args[1]) == 0)
			g_data.exit_code = 0;
		else if (chdir(args[1]) == -1)
		{
			g_data.exit_code = 1;
			ft_putstr_fd("minishell: cd: ", 2);
			perror(args[1]);
		}
	}
}

void	set_pwd(char *str)
{
	char	pwd[PATH_MAX];
	char	*join;

	getcwd(pwd, PATH_MAX);
	join = ft_strjoin(str, "=");
	if (look_for_env_index(g_data.env, str) != -1)
	{
		free(g_data.env[look_for_env_index(g_data.env, str)]);
		g_data.env[look_for_env_index(g_data.env, str)]
			= ft_strjoin(join, pwd);
	}
	free(join);
}

void	cd_cmd(char **args)
{
	char	*home;
	char	*old;

	home = ft_find_path(g_data.env, "HOME");
	old = ft_find_path(g_data.env, "OLDPWD");
	set_pwd("OLDPWD");
	g_data.exit_code = 0;
	if (!ft_strncmp(args[1], "~", 1) || !args[1])
	{
		if (!home)
		{
			ft_putendl_fd("Minishell: cd: HOME not set", 2);
			g_data.exit_code = 1;
			return ;
		}
		chdir(home);
	}
	else if (!ft_strncmp(args[1], "-", 1) || !args[1])
		chdir(old);
	else if (args[1])
		cd2(args);
	free(home);
	set_pwd("PWD");
	free(old);
}
