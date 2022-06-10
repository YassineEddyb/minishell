/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:14:11 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/10 23:21:33 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**norm1(char **args)
{
	int		i;
	int		j;
	int		x;
	char	*str;
	char	**tmp;

	tmp = malloc(sizeof(char *) * (table_len(args) + 1));
	i = 1;
	x = 0;
	while (args[i])
	{
		j = 0;
		while (g_data.env[j])
		{
			str = ft_substr(g_data.env[j], 0,
					ft_strlen_till_c(g_data.env[j], '='));
			if (ft_strncmp(args[i], str, ft_strlen(args[i])) == 0)
				tmp[x++] = args[i];
			free(str);
			j++;
		}
		i++;
	}
	tmp[x] = NULL;
	return (tmp);
}

char	**norm2(char **args, char **tmp)
{
	int		i;
	int		j;
	int		y;
	int		x;
	char	**new;

	new = malloc(sizeof(char *) * (table_len(args) + 1));
	i = 0;
	y = 1;
	new[0] = args[0];
	while (args[++i])
	{
		j = 0;
		x = 0;
		while (tmp[j])
		{
			if (ft_strncmp(args[i], tmp[j], ft_strlen(args[i])) == 0)
				x++;
			j++;
		}
		if (x == 0)
			new[y++] = args[i];
	}
	new[y] = NULL;
	return (new);
}