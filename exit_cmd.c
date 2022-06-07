/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 19:45:02 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/07 02:17:08 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_digit_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	exit_cmd(char **args)
{
	if (!args[1])
	{
		printf("exit\n");
		exit(0);
	}
	else if (!ft_digit_check(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	else if (args[2])
		printf("minishell: exit: too many arguments\n");
	else if (ft_digit_check(args[1]) && !args[2])
	{
		printf("exit\n");
		exit(ft_atoi(args[1]));
	}
}
