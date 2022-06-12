/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 01:18:49 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/12 18:39:15 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	pwd_cmd(void)
{
	char	buf[1000];

	getcwd(buf, 1000);
	printf("%s\n", buf);
}
