/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:14:11 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/18 23:44:35 by aaizza           ###   ########.fr       */
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

	tmp = malloc(sizeof(char *) * (table_len(g_data.env) + 1));
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
		j = -1;
		x = 0;
		while (tmp[++j])
		{
			if (ft_strncmp(args[i], tmp[j], ft_strlen(args[i])) == 0)
				x++;
		}
		if (x == 0)
			new[y++] = args[i];
	}
	new[y] = NULL;
	free(tmp);
	return (new);
}

int	table_len(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	help_export(int i, int j, int x)
{
	while (g_data.env[i])
	{
		printf("declare -x ");
		j = 0;
		x = 0;
		while (g_data.env[i][j])
		{
			if (g_data.env[i][j] == '=')
			{
				printf("=\"");
				x++;
				j++;
			}
			printf("%c", g_data.env[i][j]);
			j++;
		}
		if (x != 0)
			printf("\"");
		printf("\n");
		i++;
	}
}
