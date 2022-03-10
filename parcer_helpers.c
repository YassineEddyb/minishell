/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 20:20:54 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/09 14:40:59 by yed-dyb          ###   ########.fr       */
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
		if (str[i] == PIPE)
			len++;
		i++;
	}
	return len;
}

void    ft_replace(char *s, char rm, char rp, char c)
{
	int     i;

	i = 1;
	while (s[i] != c)
	{
		if (s[i] == rm)
			s[i] = rp;
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