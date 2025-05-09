/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:47:19 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/09 21:36:42 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

// Command | What It Does
// cd /path | Goes to /path
// cd | Goes to the $HOME directory
// cd - | Goes to the $OLDPWD (previous directory)
// cd relative/ | Goes to a relative directory

int		cd_builtin(t_env *env, char **args)
{
    
}
