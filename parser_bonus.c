/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 12:03:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/04/04 17:38:29 by yed-dyb          ###   ########.fr       */
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
        else if (match[j] == ASTERISK)
        {
            while(str[i] && match[j + 1] != str[i])
                i++;
            j++;
        }
        else
            break ;
    }

    if (!str[i] && !match[j])
        return (1);
    else
        return (0);
}

void parser_check_asterisk(token_t *token)
{
    struct dirent *de;
    DIR *dr;
;
    dr = opendir(".");
    while ((de = readdir(dr)) != NULL)
    {
        if (is_match(de->d_name, token->value))
            data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, de->d_name, -1);
    }
    closedir(dr);
}