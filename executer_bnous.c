/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_bnous.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:48:35 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/08 19:34:49 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_and_and_or(int process_index)
{
	int	i;
	int	status;

	if (g_data.cmds[process_index].and || g_data.cmds[process_index].or)
	{
		i = 0;
		while (i < process_index + 1)
		{
			waitpid(-1, &status, 0);
			i++;
		}
		if (g_data.cmds[process_index].and)
		{
			if (WEXITSTATUS(status) != 0)
				return (0);
		}
		else if (g_data.cmds[process_index].or)
		{
			if (WEXITSTATUS(status) == 0)
				return (0);
		}
	}
	return (1);
}
