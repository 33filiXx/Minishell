/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:37:35 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/17 18:15:30 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

void	init_exc(t_command *cmd, t_env *env)
{
	if (!cmd || !cmd->argv[0])
		return;
    if (ft_strcmp(cmd->argv[0], "cd") == 0)
		cd_builtin(env, &cmd->argv[0]);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		pwd_builtin(env);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		echo_builtin(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		export_builtin(&env, cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
    {
        if (cmd->argv[1])
            unset_env(&env, cmd->argv[1]);
        else
            fprintf(stderr, "unset: not enough arguments\n");
    }
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		    print_env(env);
    else
        fprintf(stderr, "minishell: command not found: %s\n", cmd->argv[0]);
}