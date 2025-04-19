#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../ft_libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum tokens
{
	PIPE,
	TRUNC,
	HERDOC,
	APPEND,
	WORD,

}					e_tokens;

typedef struct s_lexer
{
	e_tokens		token;
	char			*content;
	struct s_lexer	*next;
}					t_lexer;

t_lexer				*creat_node(char *content);
void				insert_at_end(t_lexer **head, char *content);
void				parsing(char **argv);

#endif