/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:40:07 by aaizza            #+#    #+#             */
/*   Updated: 2022/05/27 20:40:25 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2d_table(char **table)
{
	int	i;

	if (table != NULL)
	{
		i = -1;
		while (table[++i])
			free(table[i]);
		free(table);
	}
}

int	table_len(char **tab)
{
	int	i;
	
	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**strdup_table(char **env)
{
	int		i;
	char	**table;

	if (env == NULL)
		return (NULL);
	i = table_len(env);
	table = (char **)malloc(sizeof(char *) * (i + 1));
	if (!table)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		table[i] = ft_strdup(env[i]);
		if (!table[i])
			return (NULL);
	}
	table[i] = NULL;
	return (table);
}

void export_cmd(char **args)
{
    int i;
    int j;
    int x;
    char    **new_env;
	char	**t;


    i = 0;
    if (!args[1])
    {
        while (data.env[i])
        {
            printf("declare -x ");
            j = 0;
            x = 0;
            while (data.env[i][j])
            {
                if (data.env[i][j] == '=')
                {
                    printf("=\"");
                    x++;
                    j++;
                }
                printf("%c", data.env[i][j]);
                j++;
            }
            if (x != 0)
                printf("\"");
            printf("\n");
            i++;
        }
	}
	else
	{
		i = table_len(args);
		t = malloc(sizeof(char *) * i);
		j = 1;
		while (j < i)
		{
			t[j] = ft_substr(args[j], 0, ft_strlen_till_c(args[j], '='));
			j++;
		}
		t[j] = NULL;
		unset_cmd(t);
		i = table_len(data.env);
		j = table_len(args) - 1;
		new_env = malloc(sizeof(char *) * (i + j + 1));
		unset_cmd(t);
		x = 0;
		while(x < i)
		{
			new_env[x] = ft_strdup(data.env[x]);
			x++;
		}
		i = 1;
		while(i < j + 1)
		{
			new_env[x++] = ft_strdup(args[i++]);
		}
		new_env[x] = NULL;
		data.env = strdup_table(new_env);
		ft_free_2d_table(new_env);
	}
}