/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/16 12:51:20 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int ac , char **av, char **env)
{
    char *str;
	(void)ac;
	(void)av;
	(void)env;

	// env[1] = "SHELL=minishell";
	// env[15] = "PWD=/Users/yed-dyb/Desktop/cursus";
	while(1)
	{
       	str = readline("\033[0;32mminishell:$ \x1B[37m");
		if (str[0])
		{
			add_history(str);
      		parser(str);
			//printf("%s,%s\n", data.input, data.output);
		 	execute(&data, env);
			clean_data();
			//system("leaks minishell");
		}
	}

	//printf("%s,%s\n", data.input, data.output);
	// int i = 0;
	// int j;
	// while (i < data.num_of_cmds)
	// {
	// 	printf("%s\n", data.cmds[i].path);
	// 	j = 0;
	// 	while(data.cmds[i].args[j])
	// 	{
	// 		printf("%s\n", data.cmds[i].args[j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
}