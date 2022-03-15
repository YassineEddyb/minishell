/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:09:20 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/14 21:07:44 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    check_for_path(char **arr, char *command, int i)
{
	int		j;
	int		a;
	char	*path;

	if (!arr)
		return ;
	j = 0;
	while (arr[j])
	{
		data.cmds[i].path = NULL;
		path = ft_strjoin(arr[j], command);
		a = access(path, F_OK);
		if (a == 0)
		{
			data.cmds[i].path = path;
			break ;
		}
		free(path);
		j++;
	}
}

void    get_path(char **arr)
{
	int		i;
	char	*command;

	i = 0;
	while (i < data.num_of_cmds)
	{
		pipe(data.cmds[i].p);
		command = ft_strjoin("/", data.cmds[i].args[0]);
		check_for_path(arr, command, i);
		free(command);
		i++;
	}
}

void get_args()
{
	int i;

	i = 0;
	while(i < data.num_of_cmds)
	{
        data.cmds[i].args = ft_split(data.cmds[i].str, -1);
        i++;
	}
}

static void parser_parse(token_t *token, lexer_t *lexer)
{
    if (token->type == TOKEN_WORD)
        data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, token->value, -1);
    else if (token->type == TOKEN_DOLLAR_SIGN)
        data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, getenv(lexer_get_next_token(lexer)->value), -1);
    else if (token->type == TOKEN_STRING_SINGLE_QUOTES)
        data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, token->value, -1);
    else if (token->type == TOKEN_LESS_THAN)
        data.input = lexer_get_next_token(lexer)->value;
    else if (token->type == TOKEN_OLD_THAN)
        data.output = lexer_get_next_token(lexer)->value;
    else if (token->type == TOKEN_PIPE)
        data.index++;
        
}

void init_data(char *str)
{
    int i;

    data.num_of_cmds = get_num_of_cmds(str);
    data.index = 0;
    data.cmds = malloc(data.num_of_cmds * sizeof(t_cmd));
    i = 0;
    
    while(i < data.num_of_cmds)
    {
        data.cmds[i].str = NULL;
        i++;
    }
}

void parser(char *str)
{
    lexer_t *lexer;
    token_t *token;
    char **arr;

    init_data(str);
    arr = ft_split(getenv("PATH"), ':');
    lexer = init_lexer(str);
    token = lexer_get_next_token(lexer);
    parser_parse(token, lexer);
    while(token->type)
    {
        token = lexer_get_next_token(lexer);
        parser_parse(token, lexer);
    }
    get_args();
    get_path(arr);

    // int i = 0;
    // int j;
    // while(i < data.num_of_cmds)
    // {
    //     printf("%s\n", data.cmds[i].path);
    //     j = 0;
    //     while(data.cmds[i].args[j])
    //     {
    //         printf("%s\n", data.cmds[i].args[j]);
    //         j++;
    //     }
    //     i++;
    // }
}