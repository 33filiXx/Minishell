/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:47:19 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/10 21:26:07 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

// Command | What It Does
// cd /path | Goes to /path
// cd | Goes to the $HOME directory
// cd - | Goes to the $OLDPWD (previous directory)
// cd relative/ | Goes to a relative directory

int	cd_builtin(t_env *env, char **args)
{
	char	*home_path;
	char	*target_path;
	char	*old_path;

	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		home_path = get_env_value(env, "HOME");
		if (!home_path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
		target_path = home_path;
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		old_path = get_env_value(env, "OLDPWD");
		if (!old_path)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (1);
		}
		target_path = old_path;
	}
	else
		target_path = args[1];
	if(chdir(target_path) == -1)
	{
		fprintf(stderr, "minishell: cd");
		return (1);
	}
	set_env_value(&env, "OLDPWD", get_env_value(env, "PWD"));
	set_env_value(&env, "PWD", getcwd(NULL, 0));
	return (0);
}
