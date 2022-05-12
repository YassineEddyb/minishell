/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 01:49:53 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/05/12 17:59:03 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char **dup_arr(char **arr)
{
    int i = 0;
    char **new_arr;
    new_arr = malloc((get_arr_size(arr) + 1) * sizeof(char *));
    while(arr[i])
    {
        new_arr[i] = ft_strdup(arr[i]);
        i++;
    }
    new_arr[i] = NULL;
    return (new_arr);
}

void unset_cmd(char **args)
{
    int i = 0;
    int j = 1;
    int k = 0;
    int exist = 0;
    char **new_env;

    if (args[1])
    {
        printf("UNSETTTT\n");
        // while(data.env[i])
        // {
        //     printf("%s\n", data.env[i]);
        //     i++;
        // }
        while(args[j])
        {
            new_env = malloc((get_arr_size(data.env) + 1) * sizeof(char *));
            i = 0;
            while(data.env[i])
            {
                if (!ft_strncmp(data.env[i], args[j], ft_strlen(args[j]))
                        && (data.env[i][ft_strlen(args[j])] == '=' || data.env[i][ft_strlen(args[j])] == '\0'))
                    i++;
                if (data.env[i])
                    new_env[k++] = ft_strdup(data.env[i]);
                i++;
            }
            new_env[k] = NULL;
            k = 0;
            data.env = dup_arr(new_env);
            free_arr(new_env);
            j++;
        }
    }
}