/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 19:45:02 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/12 10:20:20 by yed-dyb          ###   ########.fr       */
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
		ft_print_error("minishell: exit: `", args[1],
			": numeric argument required\n");
		exit(255);
	}
	else if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_data.exit_code = 1;
	}
	else if (ft_digit_check(args[1]) && !args[2])
	{
		printf("exit\n");
		exit(ft_atoi(args[1]));
	}
}
