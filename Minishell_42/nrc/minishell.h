/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:26:08 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/17 16:00:18 by wel-mjiy         ###   ########.fr       */
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

#define REDIR_IN   1  // <
#define REDIR_OUT  2  // >
#define REDIR_APPEND 3 // >>
#define HEREDOC    4  // <<

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

typedef struct s_redirection {
	int  type;              // 1: <, 2: >, 3: >>, 4: << mt3l9a bdik define li dart lik
    char *filename;        // e.g., "output.txt"
    struct s_redirection *next;
} t_redirection;

typedef struct s_command {
    char **argv;                // e.g., {"grep", "hello", NULL}
    t_redirection *redirs;       // linked list of redirections
    int pipe_in;                 // 1 if input is from previous pipe tanchra7om lik hado ra shalin
    int pipe_out;                // 1 if output goes to next pipe
    struct s_command *next;      // next command in pipe chain
} t_command;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

t_lexer				*creat_node(char *content, e_tokens token);
void				insert_at_end(t_lexer **head, char *content,
						e_tokens token);
void				parsing(char *argv, t_lexer **lexer);
void				ft_free_nodes(t_lexer *lexer);
int					ft_strcmp(const char *s1, const char *s2);
void				parser(t_lexer *lexer, t_command **command_list);
// exec builtin
int		echo_builtin(char **args);
int		pwd_builtin(t_env *env);
int		cd_builtin(t_env *env, char **args);
// int		exit_builtin(char **args);
// int		env_builtin(t_env *env);
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