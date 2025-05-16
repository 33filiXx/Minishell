/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:47:23 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/11 20:09:54 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

// 1. Initialize empty list head = NULL
// 2. For each envp[i] until NULL:
//    a. Split envp[i] into key and value (at first '=')
//    b. Create a new t_env node with key and value
//    c. Add the new node to the list
// 3. Return the head of the list
// 1. malloc(sizeof(t_env))
// 2. node->key = strdup(key)
// 3. node->value = strdup(value)
// 4. node->next = NULL
// 5. return node

/*how unset worl
When the user runs unset VAR_NAME, this function is called.

It searches for the node in your linked list with a key that matches VAR_NAME.

If it finds it:

It disconnects it from the list.

It frees the memory of that node (no memory leaks).

If it doesn’t find the key, it does nothing.
*/

t_env	*env_node_new(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = *lst;
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while ((tmp)->next != NULL)
			(tmp) = (tmp)->next;
		tmp->next = new;
	}
}

t_env	*init_env(char **envp)
{
    t_env	*env;
    int		i;
	char	*key;
	char	*value;
	char	*equal;

    i = 0;
    env = NULL;
    while (envp[i])
    {
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			key = ft_substr(envp[i], 0, equal - envp[i]);
			value = ft_strdup(equal + 1);
			env_add_back(&env, env_node_new(key, value));
			free(key);
			free(value);
		}
		else
			env_add_back(&env, env_node_new(envp[i], NULL));
        i++;
    }
    return (env);
}

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp((tmp)->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = env_node_new(key, value);
	env_add_back(env, new);
}

void	clear_env(t_env **env)
{
    t_env *tmp;

    while (*env)
    {
        tmp = *env;
        free(tmp->key);
        free(tmp->value);
        *env = tmp->next;
        free(tmp);
    }
    *env = NULL;
}

void	init_minimal_env(t_env **env)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)))
        set_env_value(env, "PWD", cwd);
    set_env_value(env, "SHLVL", "1");
    set_env_value(env, "_", "");
}

void	print_env(t_env *env)
{
	if (!env)
    {
        clear_env(&env);
        init_minimal_env(&env);
    }
	while (env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
