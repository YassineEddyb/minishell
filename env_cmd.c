/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:32:22 by aaizza            #+#    #+#             */
/*   Updated: 2022/05/27 18:54:10 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_xhar (char *str, char c)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return 1;
		i++;
	}
	return 0;
}

void	env_cmd()
{
	int	i;

	i = 0;
	while (data.env[i])
	{
		if (find_xhar(data.env[i], '='))
			printf("%s\n", data.env[i]);
		i++;
	}
	exit(0);
}