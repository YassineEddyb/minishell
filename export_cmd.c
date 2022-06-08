/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:40:07 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/08 18:54:26 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	help_export(char **args, int i, int j, int x)
{
	while (g_data.env[i])
	{
		printf("declare -x ");
		j = 0;
		x = 0;
		while (g_data.env[i][j])
		{
			if (g_data.env[i][j] == '=')
			{
				printf("=\"");
				x++;
				j++;
			}
			printf("%c", g_data.env[i][j]);
			j++;
		}
		if (x != 0)
			printf("\"");
		printf("\n");
		i++;
	}
}

void	help_export1(char **args, int i, int j)
{
	char	**t;

	i = table_len(args);
	t = malloc(sizeof(char *) * (i + 1));
	j = -1;
	while (++j < i)
		t[j] = ft_substr(args[j], 0, ft_strlen_till_c(args[j], '='));
	t[j] = NULL;
	unset_cmd(t, 1);
}

int	help_export2(char **args, int i, int j, int x)
{
	char	**new_env;

	i = table_len(g_data.env);
	j = table_len(args) - 1;
	new_env = malloc(sizeof(char *) * (i + j + 1));
	x = 0;
	while (x < i)
	{
		new_env[x] = ft_strdup(g_data.env[x]);
		x++;
	}
	i = 1;
	while (i < j + 1)
	{
		if (!ft_isalpha(args[i][0]) || !ft_check_alnum2(args[i] + 1))
		{
			printf("minishell: export: `%s':not a valid identifier\n",
					args[i++]);
		}
		else
			new_env[x++] = ft_strdup(args[i++]);
	}
	new_env[x] = NULL;
	free(g_data.env);
	g_data.env = new_env;
	return (0);
}

void	export_cmd(char **args)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	if (!args[1])
	{
		help_export(args, i, j, x);
		g_data.exit_code = 0;
	}
	else
	{
		help_export1(args, i, j);
		(help_export2(args, i, j, x));
	}
}
