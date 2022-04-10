/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 12:03:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/04/09 17:56:26 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int is_match(char *str, char *match)
{
    int i;
    int j;

    i = j = 0;
    while(str[i] && match[j])
    {
        if (str[i] == match[j])
        {
            i++;
            j++;
        }
        if (match[j] == ASTERISK)
        {
            while(str[i] && match[j + 1] != str[i])
                i++;
            j++;
        }
        else if (str[i] != match[j])
            break ;
    }
    if (!str[i] && !match[j])
        return (1);
    else
        return (0);
}

void parser_check_asterisk(token_t *token)
{
    int i;
    struct dirent *de;
    DIR *dr;

    dr = opendir(".");
    i = 0;
    while ((de = readdir(dr)) != NULL)
    {
        if (is_match(de->d_name, token->value) && de->d_name[0] != '.')
        {
            data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, de->d_name, -1);
            i++;
        }
    }
    closedir(dr);
    if (i == 0)
    {
        ft_putstr_fd("minishell: no matches found: ", 2);
        ft_putstr_fd(token->value,2);
        ft_putstr_fd("\n", 2);
        data.err = 1;
    }
}