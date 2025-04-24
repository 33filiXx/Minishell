#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../ft_libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum tokens {
	PIPE,
	TRUNC,
	HERDOC,
	APPEND, 
}	e_tokens;


typedef struct s_lexer {
	e_tokens token;
	char *content;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_command {
	char *name;                
	char **args;              
	char *input_file;         
	char *output_file;        
	char *append_file;        
	char *heredoc_delimiter;  
	int pipe_in;               
	int pipe_out;       
	int saved_stdin;    
	int saved_stdout;
}	t_command;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

t_lexer *creat_node(char *content);
void add_front(t_lexer **head , char *content);
void	insert_at_end(t_lexer **head, char *content);

// exec builtin
int	echo_builtin(char **args);
int	pwd_builtin(void);

#endif