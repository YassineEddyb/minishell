/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:09:20 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/04/08 23:14:24 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

token_t parser_expect(lexer_t *lexer, token_t *token, int token_type)
{
    token_t new_token;

    new_token = lexer_get_next_token(lexer);
    if (new_token.type == token_type || new_token.type == TOKEN_DOLLAR_SIGN)
    {
        return (new_token);
    }
    else
        parser_error(new_token.value);
}

void parser_handle_dollar_sign(lexer_t *lexer, token_t *token)
{
	token_t tok;

	tok = lexer_get_next_token(lexer);
	if (tok.type == TOKEN_WORD)
	{
		if (starts_with(tok.value, QUESTION_MARK))
		{
			tok.value = ft_strjoin("$", tok.value);
			data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, parser_handle_string(&tok), -1);
		}
		else
			data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, getenv(tok.value), -1);
	}
	else
		parser_parse(&tok, lexer);
}

void parser_parse(token_t *token, lexer_t *lexer)
{
    char *str;

    str = data.cmds[data.index].str;
    if (token->type == TOKEN_WORD)
        parser_handle_word(token);
    else if (token->type == TOKEN_DOLLAR_SIGN)
		parser_handle_dollar_sign(lexer, token);
    else if (token->type == TOKEN_STRING_SINGLE_QUOTES)
        str = join_with_sep(str, token->value, -1);
    else if (token->type == TOKEN_STRING_DOUBLE_QUOTES)
        str = join_with_sep(str, parser_handle_string(token), -1);
    else if (token->type == TOKEN_PARENTHESES)
        data.cmds[data.index].str = join_with_sep(ft_strdup("./minishell"), token->value, -1);
    else if (token->type == TOKEN_LESS_THAN)
        data.input = parser_expect(lexer, token, TOKEN_WORD).value;
    else if (token->type == TOKEN_OLD_THAN)
        data.cmds[data.index].output = parser_expect(lexer, token, TOKEN_WORD).value;
    else if (token->type == TOKEN_LESS_LESS)
        parser_handle_append_redirect(token, lexer);
    else if (token->type == TOKEN_GREAT_GREAT)
    {
        data.append = 1;
        data.cmds[data.index].output = parser_expect(lexer, token, TOKEN_WORD).value;
    }
    else
        parser_set_and_increment(token);
}

void init_data(char *str)
{
    int i;

    data.num_of_cmds = get_num_of_cmds(str);
    data.index = 0;
    data.heredoc = 0;
    data.append = 0;
    data.err = 0;
    data.cmds = malloc(data.num_of_cmds * sizeof(t_cmd));
    i = 0;
    while(i < data.num_of_cmds)
    {
        data.cmds[i].pipe = 0;
        data.cmds[i].and = 0;
        data.cmds[i].or = 0;
        data.cmds[i].args = NULL;
        data.cmds[i].str = NULL;
        data.cmds[i].path = NULL;
		data.cmds[i].output = NULL;
        i++;
    }
}

void parser(char *str)
{
    lexer_t *lexer;
    token_t token;
    token_t temp_token;

    init_data(str);
    lexer = init_lexer(str);
    token = lexer_get_next_token(lexer);
    parser_parse(&token, lexer);
    temp_token = token;
    free(token.value);
    while(token.type)
    {
        token = lexer_get_next_token(lexer);
        if (parser_expect_new_line(temp_token.type) && token.type == TOKEN_END)
        {
            parser_error("NEW_LINE");
            break;
        }
        parser_parse(&token, lexer);
        temp_token = token;
        free(token.value);
    }
    free(lexer);
    get_path_and_args();

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