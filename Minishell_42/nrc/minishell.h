/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:26:08 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/13 21:53:09 by ykhoussi         ###   ########.fr       */
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

t_lexer				*creat_node(char *content, e_tokens token);
void				insert_at_end(t_lexer **head, char *content,
						e_tokens token);
void				parsing(char *argv, t_lexer *lexer);
void				ft_free_nodes(t_lexer *lexer);
int					ft_strcmp(const char *s1, const char *s2);

// exec builtin
int		echo_builtin(char **args);
int		pwd_builtin(t_env *env);
int		cd_builtin(t_env *env, char **args);
int		exit_builtin(char **args);
int		env_builtin(t_env *env);
int		export_builtin(t_env **env, char **args);
void	print_env_export(t_env *env);
void	unset_env(t_env **env, const char *key);

//env_handel
t_env	*env_node_new(const char *key, const char *value);
void    env_add_back(t_env **lst, t_env *new);
t_env	*init_env(char **envp);
char	*get_env_value(t_env *env, const char *key);
void	set_env_value(t_env **env, const char *key, const char *value);
void	unset_env(t_env **env, const char *key);
void    print_env(t_env *env);

// memory_management
void	free_split(char **s);

#endif