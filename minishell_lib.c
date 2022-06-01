/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:08:00 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/01 10:54:49 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_arr_size(char **arr)
{
    int i = 0;
    while(arr[i])
        i++;
    return (i);
}

int	get_index(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

int	starts_with(char *str, char c)
{
	if (!str || !str[0])
		return (1);
	if (str[0] == c)
		return (1);
	else
		return (0);
}

char *join_and_free(char *s1, char *s2)
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

void free_if_exists(char *str)
{
	if (str)
		free(str);
	str = NULL;
}