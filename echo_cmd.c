/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:57:40 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/28 13:55:13 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void echo_cmd(char **args)
{
    int i;
    int new_line;

    i = 1;
    new_line = 1;
    if (args[i] && !strncmp(args[i], "-n", 3))
    {
        i++;
		new_line = 0;
    }
    while(args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	exit(0);
}