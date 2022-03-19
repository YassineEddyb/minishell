/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:09:20 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/19 08:57:40 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static char *parser_collect_string(lexer_t *lexer, char c)
{
    int i;
    char *val;

    val = malloc(lexer_strlen(lexer, c) + 1 * sizeof(char));
    i = 0;
    while(lexer->c != c && lexer->c != '\0')
    {
        val[i] = lexer->c;
        lexer_next_char(lexer);
        i++;
    }
    val[i] = '\0';
    return (val);
}

static char *parser_handle_string(token_t *token)
{
    int i;
    char *str = NULL;
    lexer_t *lexer = init_lexer(token->value);

    while(lexer->c != '\0')
    {
        if (lexer->c != DOLLAR_SIGN)
            str = ft_strjoin(str ,parser_collect_string(lexer, DOLLAR_SIGN));
        else if (lexer->c == DOLLAR_SIGN)
        {
            lexer_next_char(lexer);
            str = ft_strjoin(str,getenv(parser_collect_string(lexer, SPACE)));
        }
    }
    free(lexer);
    return (str);
}

// void parser_parse_token_and_free(lexer_t *lexer, char *str)
// {
    
// }

static void parser_parse(token_t *token, lexer_t *lexer)
{
    char *val;

    if (token->type == TOKEN_WORD)
        data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, token->value, -1);
    else if (token->type == TOKEN_DOLLAR_SIGN)
    {
        val = lexer_get_next_token(lexer).value;
        data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, getenv(val), -1);
        free(val);
    }
    else if (token->type == TOKEN_STRING_SINGLE_QUOTES)
        data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, token->value, -1);
    else if (token->type == TOKEN_STRING_DOUBLE_QUOTES)
        data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, parser_handle_string(token), -1);
    else if (token->type == TOKEN_LESS_THAN)
        data.input = lexer_get_next_token(lexer).value;
    else if (token->type == TOKEN_OLD_THAN)
        data.output = lexer_get_next_token(lexer).value;
    else if (token->type == TOKEN_LESS_LESS)
    {
        data.heredoc = 1;
        data.limit = lexer_get_next_token(lexer).value;
        data.input = NULL;
        if(data.cmds[0].str == NULL)
        {
            data.cmds[0].path = ft_strdup("/bin/cat");
            data.cmds[0].args = ft_calloc(2, sizeof(char *));
            data.cmds[0].args[0] = ft_strdup("cat");
        }
    }
    else if (token->type == TOKEN_GREAT_GREAT)
    {
        //printf("OK\n");
        data.append = 1;
        data.output = lexer_get_next_token(lexer).value;
    }
    else if (token->type == TOKEN_PIPE)
        data.index++;
}

void init_data(char *str)
{
    int i;

    data.num_of_cmds = get_num_of_cmds(str);
    data.index = 0;
    data.heredoc = 0;
    data.append = 0;
    data.cmds = malloc(data.num_of_cmds * sizeof(t_cmd));
    i = 0;
    while(i < data.num_of_cmds)
    {
        data.cmds[i].str = NULL;
        data.cmds[i].path = NULL;
        i++;
    }
}

void parser(char *str)
{
    lexer_t *lexer;
    token_t token;

    init_data(str);
    lexer = init_lexer(str);
    token = lexer_get_next_token(lexer);
    parser_parse(&token, lexer);
    free(token.value);
    while(token.type)
    {
        //printf("%s\n", token.value);
        token = lexer_get_next_token(lexer);
        parser_parse(&token, lexer);
        free(token.value);
    }
    free(lexer);
    get_path_and_args();

    // int i = 0;
    // int j;
    // while(i < data.num_of_cmds)
    // {
    //     printf("%s\n[", data.cmds[i].path);
    //     j = 0;
    //     while(data.cmds[i].args[j])
    //     {
    //         printf("%s, ", data.cmds[i].args[j]);
    //         j++;
    //     }
    //     i++;
    // }
    //printf("\n%s, %s\n", data.input, data.output);
}