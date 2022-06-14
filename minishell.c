/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:15:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/14 18:24:54 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cntr_c(void)
{
	g_data.exit_code = 1;
	if (g_data.heredoc_signal == 1)
	{
		g_data.close_heredoc = 1;
		printf("\n");
		close(0);
	}
	else if (g_data.child_signal)
	{
		printf("\n");
		g_data.cntr_c = 1;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
		handle_cntr_c();
	else if (sig == SIGQUIT)
	{
		if (g_data.child_signal)
		{
			printf("\n");
			rl_redisplay();
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	minishell(char *str)
{
	while (1)
	{
		str = readline("\033[0;32mminishell:$ \x1B[0m");
		if (!str)
		{
			printf("exit\n");
			exit(0);
		}
		if (str[0])
		{
			add_history(str);
			parser(str);
			free_if_exists(str);
			execute();
			clean_data();
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
	g_data.pwd = getenv("PWD");
	g_data.env = strdup_table(env);
	g_data.fd = dup(0);
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
