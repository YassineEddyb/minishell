/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:40:07 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/12 19:46:01 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_export(int i, int j, int x)
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
	ft_free_2d_table(t);
}

int	export2(int x, int j, char **args, char **new_env)
{
	int	i;
	int	z;

	i = 1;
	z = 0;
	while (i < j + 1)
	{
		if (!ft_isalpha2(args[i][0]) || !ft_check_alnum2(args[i] + 1))
		{
			ft_print_error("minishell: unset: `",
				args[i++], "':not a valid identifier\n");
			z++;
		}
		else
			new_env[x++] = ft_strdup(args[i++]);
	}
	new_env[x] = NULL;
	ft_free_2d_table(g_data.env);
	g_data.env = new_env;
	return (z);
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
	return (export2(x, j, args, new_env));
}

void	export_cmd(char **args)
{
	int		i;
	int		x;
	char	**str;

	i = 0;
	if (!args[1])
		help_export(i, 0, 0);
	else
	{
		str = norm2(args, norm1(args));
		help_export1(str, i, 0);
		x = help_export2(str, i, 0, 0);
		if (x == 0)
			g_data.exit_code = 0;
		else
			g_data.exit_code = 1;
		free(str);
	}
}
