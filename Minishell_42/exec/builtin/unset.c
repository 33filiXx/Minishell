/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:10:14 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/13 21:54:29 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

void	unset_env(t_env **env, const char *key)
{
	t_env = tmp;
	if (!env || !key)
		return;
	while (*env)
	{
		if (!ft_strcmp((*env)->key, key))
		{
			
		}
		(*env) = (*env)->next;
	}
		
}
