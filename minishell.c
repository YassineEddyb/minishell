/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/08 13:41:47 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int ac , char **av, char **env)
{
    t_data data;
    char *str;
	(void)ac;
	(void)av;

    str = readline("minishell > ");

    parce(&data, str, env);
	int i = 0;
	int j;
	while (i < data.num_of_cmds)
	{
		printf("%s\n", data.cmds[i].path);
		j = 0;
		while(data.cmds[i].args[j])
		{
			printf("%s\n", data.cmds[i].args[j]);
			j++;
		}
		i++;
	}
}