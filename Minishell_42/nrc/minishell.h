/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:26:08 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/26 08:59:39 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../ft_libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum t_tokens
{
	PIPE, // | 
	TRUNC, // >
	HERDOC, // << 
	APPEND, // >>
	INPUT, //  <
	WORD, // commend
}					e_tokens;

typedef struct s_lexer
{
	e_tokens		token;
	char			*content;
	struct s_lexer	*next;
}					t_lexer;

t_lexer				*creat_node(char *content, e_tokens token);
void				insert_at_end(t_lexer **head, char *content,
						e_tokens token);
void				parsing(char *argv, t_lexer *lexer);
int	ft_strcmp(char *s1, char *s2);
void ft_free_nodes(t_lexer *lexer);

// exec builtin
int	echo_builtin(char **args);
int	pwd_builtin(void);

#endif