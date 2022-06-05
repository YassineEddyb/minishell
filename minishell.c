/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/05 17:41:56 by yed-dyb          ###   ########.fr       */
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

	data.env = strdup_table(env);
	if (ac == 1)
	{
		while(1)
		{
			str = readline("\033[0;32mminishell:$ \x1B[0m");
			if (!str)
				exit(0);
			if (str[0])
			{
				add_history(str);
				parser(str);
				free_if_exists(str);
				execute();
				clean_data();
				// system("leaks minishell");
			}
		}
	} else if (ac == 2)
	{
		parser(av[1]);
		execute();
		clean_data();
	}
	return (data.exit_code);
}