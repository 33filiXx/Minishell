/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:27:30 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/12 20:55:31 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

// The export command in Bash is used to:

// Display all environment variables (if no arguments).

// Add a new environment variable.

// Update an existing environment variable.

// t_env	*sort_env(t_env *env)
// {

// }

int	is_valid_identifier(char *s)
{
	int	i;

	i = 1;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (1);
	if (s[i])
	{	while (s[i])
		{
			if (!ft_isalnum(s[i]))
				return (1);
			i++;
		}
	}
	else
		return (0);
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

	i = 1;
	if (!args[1])
		print_env_export(*env);
	while (args[i])
	{
		
	}
	return (0);
}
