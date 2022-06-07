/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:32:22 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/07 10:50:40 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char **args)
{
	int	i;

	i = 0;
	while (data.env[i])
	{
		if (ft_strchr(data.env[i], '='))
			printf("%s\n", data.env[i]);
		i++;
	}
	data.exit_code = 0;
}
