/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:57:40 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/07 10:51:05 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simlify_newline(char **args)
{
	int	i;
	int	j;
	int	x;

	i = -1;
	x = 1;
	if (ft_strlen(args[1]) == 1 && args[1][0] == '-')
		return (x + 1);
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
	}
	return (x);
}

void	echo_cmd(char **args)
{
	int	i;
	int	new_line;

	i = simlify_newline(args);
	new_line = 1;
	if (i > 1)
		new_line = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	data.exit_code = 0;
}
