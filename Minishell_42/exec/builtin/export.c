/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:27:30 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/13 21:34:38 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

// The export command in Bash is used to:

// Display all environment variables (if no arguments).

// Add a new environment variable.

// Update an existing environment variable.
/*export                # Shows all environment variables sorted
export NEW_VAR        # Adds NEW_VAR with NULL value
export NEW_VAR=Hello  # Updates NEW_VAR value to Hello
export INVALID-KEY=1  # Error: not a valid identifier
*/

int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (1);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	print_env_export(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

void	equal_sign(char *arg, char **key, char **value)
{
	char	*equal;
	
	equal = strchr(arg, '='); 
	if (equal)
	{
		*key = ft_substr(arg, 0, equal - arg);
		*value = ft_strdup(equal + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}

void	plus_sign(t_env **env, char *arg, char **key, char **value)
{
	char	*equal;
	char	*exist_value;
	char	*new;

	equal = strchr(arg, '=');
	if (equal)
	{
		*key = ft_substr(arg, 0, equal - arg);
		*value = ft_strdup(equal + 1);
		
		exist_value = get_env_value(*env, *key);
		if (exist_value)
		{
			new = ft_strjoin(exist_value, *value);
			set_env_value(env, *key, new);
			free(new);
		}
		else
			set_env_value(env, *key, *value);
	}
}

int	export_builtin(t_env **env, char **args)
{
	int	i;
	char	*key;
	char	*value;

	i = 1;
	if (!args[1])
		print_env_export(*env);
	while (args[i])
	{
		if (strchr(args[i], '+') != NULL)
            plus_sign(env, args[i], &key, &value);
		else
		{
			equal_sign(args[i], &key, &value);
			if (is_valid_identifier(key))
				fprintf (stderr, "export: `%s`: not a valid identifier\n", key);
			else
				set_env_value(env, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}
