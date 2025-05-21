/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:12:37 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/21 17:04:22 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

int	count_commands(t_command *cmd)
{
	int count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	close_all_pipes(int **pipes, int count)
{
	int i = 0;

	while (i < count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	execute_pipeline(t_command *cmd, t_env *env)
{
    int count;
    int i;
	int	j;
    int status;
    int **pipes;
    pid_t pid;
    char **envp;
    t_command *current;

    i = 0;
	j = 0;
    current = cmd;
    count = count_commands(cmd);
    envp = list_to_char_array(env);
    pipes = malloc(sizeof(int *) * (count - 1));

    while (i < count -1)
    {
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			exit(1);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
    }
    i = 0;
	while (current)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork faild");
			exit(1);
		}
		else if (pid == 0)
		{
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < count - 1)
				dup2(pipes[i][1], STDOUT_FILENO);	
			j = 0;
			close_all_pipes(pipes, count);
			if (current->redirs)
				redirections(current);
			if (!current->argv[0])
			{
				exit(127);
			}
			execve(current->path, current->argv, envp);
			perror("execve failed");
			exit(1);
		}
		else 
		{
			i++;
			current = current->next;
		}
	}
	j = 0;
	i = 0;
	close_all_pipes(pipes, count);
	while (j < count -1)
	{
		free(pipes[j]);
        j++;
	}
	free(pipes);
	while (i < count)
    {
        wait(&status);
        i++;
    }
	free_split(envp);
}

