/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_bnous.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:48:35 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/06 17:34:26 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_and_and_or(int process_index)
{
	int	i;
	int	status;

	if (data.cmds[process_index].and || data.cmds[process_index].or)
	{
		i = 0;
		while (i < process_index + 1)
		{
			waitpid(-1, &status, 0);
			i++;
		}
		if (data.cmds[process_index].and)
		{
			if (WEXITSTATUS(status) != 0)
				return (0);
		}
		else if (data.cmds[process_index].or)
		{
			if (WEXITSTATUS(status) == 0)
				return (0);
		}
	}
	return (1);
}
