/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:17:19 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/12 10:21:46 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	if (s2)
	{
		while (s2[j] != '\0')
			str[i++] = s2[j++];
	}
	free_if_exists(s1);
	free_if_exists(s2);
	return (str);
}

void	open_file(char *path)
{
	if (!path || path[0] == '\0')
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		g_data.err = 1;
	}
	if (!g_data.err)
		open(path, O_CREAT, 0644);
}

void	ft_print_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}
