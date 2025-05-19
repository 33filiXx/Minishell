/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:12:37 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/19 18:56:30 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

void	execute_pipeline(t_command *cmd, t_env *env)
{
    //count the cmds
    //handel cmd one by one
    // before excute should to check rediractions
    t_command	*tmp;
    int			count;
	char		**envp;
	
	envp = list_to_char_array(env);
    count = 0;
    tmp = cmd;
	while (tmp)
    {
		count++;
		tmp = tmp->next;
    }
	printf("%d\n", count);
}
