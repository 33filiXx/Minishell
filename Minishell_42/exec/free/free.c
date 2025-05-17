/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:47:19 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/17 18:05:44 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

void	free_split(char **s)
{
	int	i;

	if (!s)
		return;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
void free_redirections(t_redirection *redirs)
{
    t_redirection *tmp;

    while (redirs)
    {
        tmp = redirs;
        redirs = redirs->next;
        free(tmp->filename);
        free(tmp);
    }
}

void free_commend(t_command *cmd)
{
    t_command *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        if (cmd->argv)
        {
            for (int i = 0; cmd->argv[i]; i++)
                free(cmd->argv[i]);
            free(cmd->argv);
        }
        if (cmd->redirs)
            free_redirections(cmd->redirs);
        free(cmd);
        cmd = tmp;
    }
}

