/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:37:35 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/19 15:50:30 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

int	ft_lssize(t_env *lst)
{
	int	counter;

	if (!lst)
		return (0);
	counter = 0;
	while (lst)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}

char	**list_to_char_array(t_env *list)
{
	int		size;
	char	**array;
	int		i;

	size = ft_lssize(list);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (list)
	{
		char *full_content = ft_strjoin(list->key, "=");
		full_content = ft_strjoin(full_content, list->value);
		array[i] = ft_strdup((char *) full_content);
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	init_exc(t_command *cmd, t_env *env)
{
	if (!cmd || !cmd->argv[0])
		return 1;
    if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return cd_builtin(env, &cmd->argv[0]);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return pwd_builtin(env);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return echo_builtin(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return export_builtin(&env, cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
    {
        if (cmd->argv[1])
        {
			unset_env(&env, cmd->argv[1]);
			return 0;
		}
        else
            fprintf(stderr, "unset: not enough arguments\n");
    }
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		    return (print_env(env), 0);
    else
		excute_commend(cmd, cmd->path, cmd->argv, list_to_char_array(env));
	return 0;	
}

void	redirections(t_command *cmd)
{
	t_redirection *redir;
	int	fd;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == 1) // Input
		{	
			fd = open(redir->filename, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		else if (redir->type == 2) //Output
        {	
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (redir->type == 3) // Append
        {	
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		if (fd < 0)
		{
			perror("open failed");
			exit(1);
		}
		close(fd);
		redir = redir->next;
	}
}

void	excute_commend(t_command *cmd, char *path, char **arg, char **env)
{
	int	i;
	pid_t pid1;
	int	status;

	pid1 = fork();
	i = 0;
	if (pid1 < 0)
	{
		perror("fork faild");
		exit(1);
	}
	if (pid1 == 0)	
	{	
		if (cmd->redirs)
			redirections(cmd);
		if (execve(path, arg, env) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	else
		waitpid(pid1, &status, 0);
}
