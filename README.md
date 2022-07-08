# minishell

## subject

the subject is simply to create a minishell with some builtin commands

## implemintation

to impleminte a minishell first i need to <b>parse</b> the command and put it in a struct so that in the <b>executing</b> 
part i can just take the commands and execute them

in the order to do this i separated the project to two parts 

### parsing

in the parsing part i took the input and splited it into tokens 

```
typedef struct s_token
{
	enum {
		TOKEN_END,
		TOKEN_WORD,
		TOKEN_OLD_THAN,
		TOKEN_LESS_THAN,
		TOKEN_LESS_LESS,
		TOKEN_GREAT_GREAT,
		TOKEN_PIPE,
		TOKEN_AND_AND,
		TOKEN_PIPE_PIPE,
		TOKEN_PARENTHESES,
	}	e_type;
	char	*value;
}	t_token;
```

the <b>e_type</b> is an enum that return the index of the token assigned to it </br>
the <b>value</b> is the pyload of this token 

this porcess is called <b>lexer</b>

