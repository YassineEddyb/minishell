/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:32:22 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/10 20:02:27 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char **args)
{
	int	i;

	i = 0;
	if (args[1])
	{
		ft_putstr_fd("No rguments\n", 2);
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
