/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:28:34 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/14 20:27:47 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*ft_str_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

char *join_with_sep(char *s1, char *s2, char sep)
{
	char *str;

    str = ft_str_join(s1, lexer_get_char_as_string(sep));
    str = ft_str_join(str, s2);
	
	return (str);
}

int get_num_of_cmds(char *str)
{
	int i;
	int len;

	i = 0;
	len = 1;
	while(str[i])
	{
		if (str[i] == PIPE)
			len++;
		i++;
	}
	return len;
}