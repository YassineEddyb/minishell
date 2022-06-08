/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:23:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/08 12:10:17 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	look_for_env_index(char **env, char *start)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(start, env[i], ft_strlen(start)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	cd_cmd(char **args)
{
	char	buff[1000];
	int		old_pwd_index;
	int		pwd_index;
	char	*pwd;

	pwd = args[1];
	if (!pwd)
		pwd = ft_strdup(g_data.env[look_for_env_index(g_data.env, "HOME=")] + 5);
	old_pwd_index = look_for_env_index(g_data.env, "OLDPWD=");
	g_data.env[old_pwd_index] = \
	ft_str_join(ft_strdup("OLDPWD="), getcwd(buff, 1000));
	if (chdir(pwd) == -1)
	{
		g_data.exit_code = 1;
		perror("minishell");
		return ;
	}
	pwd_index = look_for_env_index(g_data.env, "PWD=");
	g_data.env[pwd_index] = \
	ft_str_join(ft_strdup("PWD="), getcwd(buff, 1000));
	g_data.exit_code = 0;
}
