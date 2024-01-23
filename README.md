# minishell
  __  __ _____ _   _ _____  _____ _    _ ______ _      _      
 |  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     
 | \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     
 | |\/| | | | | . ` | | |  \___ \|  __  |  __| | |    | |     
 | |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ 
 |_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|

## Subject

The subject is simply to create a minishell with some builtin commands

## Implemintation

In order To implement a minishell first We need to <b>parse</b> the command and put it in a Struct so that in the <b>executing</b> 
part we can just take the commands and execute them

<img src="./minishell_map.png" alt="minishell map" />

In the order to do this I separated the project to two parts 

### Parsing

In the parsing part I took the input and splited it into tokens 

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

<b>e_type</b>: is an enum that return the index of the token assigned to it </br>
<b>value</b>: is the pyload of this token 

This porcess is called the <b>lexer</b>

The iterate over the token and put every token in the cmd struct which hold all the necessary info to execute this command

```
typedef struct s_cmd {
	char	*str;
	char	*path;
	char	*output;
	char	*input;
	char	**args;
	int		heredoc;
	int		append;
	int		doc[2];
	int		pipe;
	int		and;
	int		or;
	int		p[2];
	int		pid;
	int		err;
}	t_cmd;
```

<b>path</b>: is the path of the command </br>
<b>output</b>: hold the output file name </br>
<b>input</b>: holds the input file name </br>
<b>args</b>: is an two dimentional arr that holds all the arguments of this commnad including the command itslef </br>
<b>heredoc</b>: 1 if I should read from the standard input and 0 if not</br>
<b>append</b>: 1 if I souuld add the result of this command to the output file and 0 if not </br>
<b>doc</b>: the pipe where the heredoc stores what his reading </br>
<b>pipe, and, or</b>: set 1 for the variable that seprates this command and the next command and 0 in the remained tow </br>
<b>p</b>: for the pipe redirection </br>
<b>err</b>: 1 if an error happen during exection part </br>

Since I have the right in only one variable I create a golbal struct where all the data is living

```
typedef struct s_data {
	char	**env;
	int		num_of_cmds;
	t_cmd	*cmds;
	int		index;
	char	*limit;
	int		err;
	int		exit_code;
	int		heredoc_signal;
	int		child_signal;
	int		close_heredoc;
	int		fd;
	char	*pwd;
}	t_data;
```

<b>env</b>: envaroment variables </br>
<b>num_of_cmds</b>: the number of commands </br>
<b>cmds</b>: the struct that holds all the commands  </br>
<b>index</b>: the index of the current command this is used where filling the cmds struct</br>
<b>err</b>: 1 if an error happen in parsing part and 0 if not</br>
<b>exit_code</b>: the exit code of this command </br>

#### Resourses

<a href="https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf" target="_blank">
	https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
</a>
</br>

<a href="https://youtu.be/WABO4o_y8qc" target="_blank">
	https://youtu.be/WABO4o_y8qc
</a>

### Executing

The executing part is quite simple since all the hard work has been done in the parsing part

I simply iterated over all command then I created a new child for each command with fork function

```
pid_t fork(void);
```

Then I changed the default <b>Standartd output</b> and <b>Standard input</b> with dup function

```
int dup2(int oldfd, int newfd);
```

After that I executed those commands with execve function

```
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

And finaly I waited all the childs to exit

```
pid_t waitpid(pid_t pid, int *stat_loc, int options);
```

But first I checked if this command is in not builtin command cause if it's a single command and builtin command I just run it in the main porcess

### Install

Run this command in your terminal :

```
git clone https://github.com/YassineEddyb/minishell && cd minishell && make && ./minishell
```

