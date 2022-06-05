/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:40:24 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/05 17:50:32 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
	int	j;
	char	**tmp;

	j = 0;
	tmp = malloc(sizeof(char *) * table_len(data.env) + 1);
	while (j < i)
	{
		tmp[j] = ft_strdup(data.env[j]);
		j++;
	}
	while (data.env[j + 1])
	{
		tmp[j] = ft_strdup(data.env[j + 1]);
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}

void	unset_cmd(char **args)
{
	char	*s1;
	char	**tmp;
	int	i;
	int	j;

	if (args[1])
	{
		i = 1;
		while (args[i])
		{
			j = 0;
			while (data.env[j])
			{
				s1 = ft_substr(data.env[j], 0, ft_strlen_till_c(data.env[j], '='));
				if (ft_strlen2(args[i]) == ft_strlen2(s1))
				{
					if(ft_strncmp(args[i], s1, ft_strlen2(s1)) == 0)
					{
						tmp = help_unset(j);
						data.env = tmp;
						break;
						// ft_free_2d_table(tmp);
					}
				}
				j++;
			}
			i++;
		}
	}
}