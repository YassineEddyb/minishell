/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:09:20 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/04/03 15:37:17 by yed-dyb          ###   ########.fr       */
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
			if (lexer->c == QUESTION_MARK)
			{
				str = ft_strjoin(str, ft_itoa(data.exit_code));
				lexer_next_char(lexer);
			}
			else
           		str = ft_strjoin(str,getenv(parser_collect_string(lexer, SPACE)));
        }
    }
    free(lexer);
    return (str);
}

token_t parser_expect(lexer_t *lexer, token_t *token, int token_type)
{
    token_t new_token;

    new_token = lexer_get_next_token(lexer);
    if (new_token.type == token_type || new_token.type == TOKEN_DOLLAR_SIGN)
    {
        return (new_token);
    }
    else
    {
        ft_putstr_fd("minishell: syntax error near unexepcted token '", STDERR);
        ft_putstr_fd(new_token.value, STDERR);
        ft_putstr_fd("'\n", STDERR);
		data.exit_code = 258;
        data.err = 1;
    }
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
    if (token->type == TOKEN_WORD)
    {
        if (ft_strchr(token->value, ASTERISK))
            parser_check_asterisk(token);
        else
            data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, token->value, -1);
    }
    else if (token->type == TOKEN_DOLLAR_SIGN)
		parser_handle_dollar_sign(lexer, token);
    else if (token->type == TOKEN_STRING_SINGLE_QUOTES)
        data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, token->value, -1);
    else if (token->type == TOKEN_STRING_DOUBLE_QUOTES)
        data.cmds[data.index].str = join_with_sep(data.cmds[data.index].str, parser_handle_string(token), -1);
    else if (token->type == TOKEN_LESS_THAN)
        data.input = parser_expect(lexer, token, TOKEN_WORD).value;
    else if (token->type == TOKEN_OLD_THAN)
        data.cmds[data.index].output = parser_expect(lexer, token, TOKEN_WORD).value;
    else if (token->type == TOKEN_LESS_LESS)
    {
        data.heredoc = 1;
        data.limit = parser_expect(lexer, token, TOKEN_WORD).value;
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
        data.append = 1;
        data.cmds[data.index].output = parser_expect(lexer, token, TOKEN_WORD).value;
    }
    else if (token->type == TOKEN_PIPE_PIPE)
    {
        data.cmds[data.index].or = 1;
        data.index++;
    }
    else if (token->type == TOKEN_AND_AND)
    {
        data.cmds[data.index].and = 1;
        data.index++;
    }
    else if (token->type == TOKEN_PIPE)
    {
        data.cmds[data.index].pipe = 1;
        data.index++;
    }
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

    init_data(str);
    lexer = init_lexer(str);
    token = lexer_get_next_token(lexer);
    parser_parse(&token, lexer);
    free(token.value);
    while(token.type)
    {
        // printf("%d\n", token.type);
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