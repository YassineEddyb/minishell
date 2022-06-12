/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:23:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/12 11:59:25 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**strdup_table(char **env)
{
	int		i;
	char	**table;

	if (env == NULL)
		return (NULL);
	i = table_len(env);
	table = (char **)malloc(sizeof(char *) * (i + 1));
	if (!table)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		table[i] = ft_strdup(env[i]);
		if (!table[i])
			return (NULL);
	}
	table[i] = NULL;
	return (table);
}

int	ft_strlen_till_c(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

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

void	cd_error(void)
{
	perror("minishell");
	g_data.exit_code = 1;
	return ;
}

void	cd_cmd(char **args)
{
	char	buff[1000];
	int		old_pwd_index;
	int		pwd_index;
	char	*pwd;

	pwd = args[1];
	if (!pwd)
		pwd = ft_strdup(g_data.env[look_for_env_index
				(g_data.env, "HOME=")] + 5);
	old_pwd_index = look_for_env_index(g_data.env, "OLDPWD=");
	free_if_exists(g_data.env[old_pwd_index]);
	g_data.env[old_pwd_index] = \
	ft_str_join(ft_strdup("OLDPWD="), getcwd(buff, 1000));
	if (chdir(pwd) == -1)
		return (cd_error());
	pwd_index = look_for_env_index(g_data.env, "PWD=");
	free_if_exists(g_data.env[pwd_index]);
	g_data.env[pwd_index] = \
	ft_str_join(ft_strdup("PWD="), getcwd(buff, 1000));
	if (!args[1])
		free(pwd);
	g_data.exit_code = 0;
}
