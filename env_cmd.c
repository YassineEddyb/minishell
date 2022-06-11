/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:32:22 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/11 22:45:36 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char **args)
{
	int	i;

	i = 0;
	if (args[1])
	{
		// ft_putstr_fd("env : : No rguments\n", 2);
		printf("env: %s: No such file or directory\n", args[1]);
		g_data.exit_code = 1;
		return ;
	}
	while (g_data.env[i])
	{
		if (ft_strchr(g_data.env[i], '='))
			printf("%s\n", g_data.env[i]);
		i++;
	}
	g_data.exit_code = 0;
}
