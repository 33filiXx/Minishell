/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:47:19 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/11 19:52:30 by ykhoussi         ###   ########.fr       */
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
	char	*new_path;

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
	else
		target_path = args[1];
	old_path = getcwd(NULL, 0);
	if(chdir(target_path) == -1)
	{
		fprintf(stderr, "minishell: cd");
		return (1);
	}
	new_path = getcwd(NULL, 0);
	if (new_path)
	{
		set_env_value(&env, "OLDPWD", old_path);
		set_env_value(&env, "PWD", new_path);
	}
	else
		fprintf(stderr, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
	return (0);
}
