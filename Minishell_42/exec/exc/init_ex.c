/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:37:35 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/16 18:23:13 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

void	init_exc(t_command *cmd, t_env *env)
{
    if(ft_strcmp(cmd->argv[0], "cd") == 0)
		cd_builtin(env, &cmd->argv[0]);
	else if(ft_strcmp(cmd->argv[0], "pwd") == 0)
		pwd_builtin(env);
}