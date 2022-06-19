/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:25:22 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/15 11:12:18 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(void)
{
	char	s[PATH_MAX];

	if (getcwd(s, sizeof(s)) != NULL)
	{
		printf("%s\n", s);
		g_data.exit_code = 0;
	}
	else
	{
		perror("minishell");
		g_data.exit_code = 1;
	}
}
