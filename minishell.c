/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/19 08:57:55 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main (int ac , char **av, char **env)
{
	struct sigaction sa;
	sa.sa_handler = &handle_signal;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

    char *str = NULL;
	(void)ac;
	(void)av;
	(void)env;

	// env[1] = "SHELL=minishell";
	// env[15] = "PWD=/Users/yed-dyb/Desktop/cursus";
	data.env = env;
	while(1)
	{
       	str = readline("\033[0;32mminishell:$ \x1B[37m");
		if (!str)
			exit(1);
		if (str[0])
		{
			add_history(str);
      		parser(str);
			free(str);
			str = NULL;
			//printf("%s,%s\n", data.input, data.output);
		 	execute();
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
	return (0);
}