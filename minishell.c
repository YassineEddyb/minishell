/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/11 17:58:33 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_data.exit_code = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	minishell(char *str)
{
	while (1)
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
			system("leaks minishell");
		}
	}
}

int	main(int ac, char **av, char **env)
{
	char				*str;
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	str = NULL;
	g_data.env = strdup_table(env);
	if (ac == 1)
		minishell(str);
	else if (ac == 2)
	{
		parser(av[1]);
		execute();
		clean_data();
	}
	return (g_data.exit_code);
}
