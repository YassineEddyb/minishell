/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:24:46 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/12 19:25:46 by aaizza           ###   ########.fr       */
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

int	ft_check_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum2(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_alnum2(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum2(str[i]))
		{
			if (str[i] == '=')
				i++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

void	ft_free_2d_table(char **table)
{
	int	i;

	if (table != NULL)
	{
		i = -1;
		while (table[++i])
			free(table[i]);
		free(table);
		table = NULL;
	}
}
