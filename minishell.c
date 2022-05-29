/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/29 20:02:25 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		data.exit_code = 1;
		// printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
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

	data.env = env;
	if (ac == 1)
	{
	// 	while(1)
	// 	{
	// 		str = readline("\033[0;32mminishell:$ \x1B[0m");
	// 		if (!str)
	// 			exit(0);
	// 		if (str[0])
	// 		{
	// 			add_history(str);
				parser("ls");
				free(str);
				str = NULL;
				execute();
				clean_data();
				system("leaks minishell");
	// 		}
	// 	}
	} else if (ac == 2)
	{
		parser(av[1]);
		execute();
		clean_data();
	}

	// int i = 0;
	// int j;
	// while (i < data.num_of_cmds)
	// {
	// 	printf("%s\n", data.cmds[i].path);
	// 	printf ("%s\n", data.cmds[i].output);
	// 	j = 0;
	// 	while(data.cmds[i].args[j])
	// 	{
	// 		printf("%s\n", data.cmds[i].args[j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
	return (data.exit_code);
}