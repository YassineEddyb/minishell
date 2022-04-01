/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:23:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/04/01 12:20:39 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int look_for_env_index(char **env, char *start)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(start, env[i], ft_strlen(start)) == 0)
			return (i);
		i++;
	}
	if (!env[i])
		return (-1);
}

void cd_cmd(char **args)
{
	int index;

	index = look_for_env_index(data.env, "PWD=");
	printf ("%d\n", index);
    char buff[100];
    data.env[index] = ft_strjoin("PWD=", getcwd(buff, 100));
    chdir(args[1]);
}