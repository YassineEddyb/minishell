/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 01:27:39 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/04/14 03:44:09 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void export_cmd(char **args)
{
    int i = 0;
    int j;
    int quote;
    char **tmp;
    if (!args[1])
    {
        while(data.env[i])
        {
            printf("declare -x ");
            j = 0;
            quote = 0;
            while(data.env[i][j])
            {
                printf("%c", data.env[i][j]);
                if (data.env[i][j] == '=' && quote == 0)
                {
                    printf("\"");
                    quote = 1;
                }
                if (quote == 1 && !data.env[i][j + 1])
                    printf("\"");
                j++;
            }
            printf("\n");
            i++;
        }
    } else
    {
        unset_cmd(args);
        tmp = malloc(sizeof (char *) * (get_arr_size(data.env) + 1 + get_arr_size(args)));
        j = -1;
        while(data.env[++j])
            tmp[j] = ft_strdup(data.env[j]);
        i = 0;
        while(args[++i])
            tmp[j++] = ft_strdup(args[i]);
        tmp[j] = NULL;
    }
    data.env = tmp;
    
}