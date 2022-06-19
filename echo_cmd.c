/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:27:49 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/19 21:13:49 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simlify_newline(char **args)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 1;
	if (ft_strlen(args[1]) == 1 && args[1][0] == '-')
		return (x);
	while (args[++i])
	{
		if (args[i][0] == '-')
		{
			j = 0;
			while (args[i][++j])
			{
				if (args[i][j] != 'n')
					return (x);
			}
			if (j > 1)
				x++;
		}
		else
			return (x);
	}
	return (x);
}

void	echo_cmd(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	if (args[1][0] == '-')
		i = simlify_newline(args);
	new_line = 1;
	if (i > 1)
		new_line = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putstr_fd(" ", 1);
	}
	if (new_line)
		printf("\n");
	g_data.exit_code = 0;
}
