/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:50:02 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/19 18:08:15 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

int	wait_for_child(pid_t child_pid)
{
	int	status;

	if (child_pid <= 0)
		return (1);
	if (waitpid(child_pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	excute_commend(t_command *cmd, char **env)
{
	int	i;
	pid_t pid1;
	int	status;

	pid1 = fork();
	i = 0;
	status = 0;
	if (pid1 < 0)
	{
		perror("fork faild");
		exit(1);
	}
	if (pid1 == 0)	
	{	
		if (cmd->redirs)
			redirections(cmd);
		if (!cmd->path)
		{
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		if (execve(cmd->path, cmd->argv, env) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	else
	{
		status = wait_for_child(pid1);
		*exit_stat() = status;
	}
}
