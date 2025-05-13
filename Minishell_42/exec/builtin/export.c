/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:27:30 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/13 17:42:14 by ykhoussi         ###   ########.fr       */
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
		if (!ft_isalnum(s[i]))
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

int	export_builtin(t_env **env, char **args)
{
	int	i;
	char	*equal;
	char	*key;
	char	*value;

	i = 1;
	if (!args[1])
		print_env_export(*env);
	while (args[i])
	{
		equal = strchr(args[i], '=');
		if (equal)
		{
			key = ft_substr(args[i], 0, equal - args[i]);
			value = ft_strdup(equal + 1);
		}
		else
		{
			key = ft_strdup(args[i]);
			value = NULL;
		}
		if (is_valid_identifier(key))
			fprintf (stderr, "export: `%s`: not a valid identifier\n", key);
		else
			set_env_value(env, key, value);
		free(key);
		free(value);
		i++;
	}
	return (0);
}
