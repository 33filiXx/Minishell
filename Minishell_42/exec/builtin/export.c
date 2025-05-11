/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:27:30 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/11 22:33:41 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

// The export command in Bash is used to:

// Display all environment variables (if no arguments).

// Add a new environment variable.

// Update an existing environment variable.

t_env	*sort_env(t_env *env)
{

}

void	print_env_export(t_env *env)
{
	while (env)
	{
		if (env->value)
			{
				printf("decared -x ");
				printf("%s=%s\n", env->key, env->value);
			}
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
		equal = ft_strchr(args[i], '=');
		if (equal)
		{
			key = ft_substr(args[i], 0, equal - args[i]);
			value = ft_strdup(equal + 1);
			set_env_value(env, key, value);
			free(key);
			free(value);
		}
		else
		{
			
		}
	}
	return (0);
}
