/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:45:59 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/16 17:19:17 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

int pwd_builtin(t_env *env)
{
    char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if(cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	else
	{
		cwd = get_env_value(env, "PWD");
		if (cwd)
			printf("%s\n", cwd);
		else
			fprintf(stderr, "pwd: error retrieving current directory\n");
		return (0);
	}
}
