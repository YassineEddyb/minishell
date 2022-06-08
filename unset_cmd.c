/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:40:24 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/08 12:10:17 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen2(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
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

char	**help_unset(int i)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = malloc(sizeof(char *) * table_len(g_data.env) + 1);
	while (j < i)
	{
		tmp[j] = ft_strdup(g_data.env[j]);
		j++;
	}
	while (g_data.env[j + 1])
	{
		tmp[j] = ft_strdup(g_data.env[j + 1]);
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}

void	help_unset1(char **args, int i, int j)
{
	char	**tmp;
	char	*s1;

	while (g_data.env[j])
	{
		s1 = ft_substr(g_data.env[j], 0, ft_strlen_till_c(g_data.env[j], '='));
		if (ft_strlen2(args[i]) == ft_strlen2(s1))
		{
			if (ft_strncmp(args[i], s1, ft_strlen2(s1)) == 0)
			{
				tmp = help_unset(j);
				g_data.env = tmp;
				break ;
			}
		}
		j++;
	}
}

void	unset_cmd(char **args, int q)
{
	int		i;
	int		j;
	char	*s;

	if (q == 0)
	{
		i = 0;
		while (args[i])
		{
			if (!ft_isalpha(args[i][0]) || !ft_check_alnum(args[i] + 1))
				printf("minishell: unset: `%s': not a valid identifier\n"
					, args[i]);
			i++;
		}
	}
	if (args[1])
	{
		i = 1;
		while (args[i])
		{
			j = 0;
			help_unset1(args, i, j);
			i++;
		}
	}
}
