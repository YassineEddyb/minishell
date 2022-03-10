/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_redirecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:36:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/10 17:24:39 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_index(char *s, char c)
{
	int i;

	i = 0;
	while(s[i] && s[i] != c)
		i++;

	return (i);
}

void check_input_output(t_data *data ,char *str)
{
	if (ft_strchr(str, LESS_THAN))
	{
		data->input = ft_substr(ft_strchr(str, LESS_THAN) + 1 , 0, get_index(ft_strchr(str, LESS_THAN), SPACE) - 1);
		str = ft_substr(ft_strchr(str, LESS_THAN) + 1 , 0, get_index(ft_strchr(str, LESS_THAN), SPACE) - 1);
	}
    if (ft_strchr(str, OLD_THAN))
		data->output = ft_substr(ft_strchr(str, OLD_THAN) + 1 , 0, get_index(ft_strchr(str, OLD_THAN), SPACE) - 1);
}

// void parce_redirecting(t_data *data, char *str)
// {
	
// }~