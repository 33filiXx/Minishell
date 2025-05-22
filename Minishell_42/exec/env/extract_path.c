/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:02:00 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/22 17:39:58 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

void	get_command_path(char **cmd, char **envp, t_command **command_list)
{
	if (cmd && ft_strchr(cmd[0], '/'))
	{
		(*command_list)->path = ft_strdup(cmd[0]);
		if (!(*command_list)->path)
			return;
	}
	else
		(*command_list)->path = extract_path(cmd[0], envp, command_list);
}

static	char	*join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*fullpath;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	fullpath = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!fullpath)
		return (NULL);
	return (fullpath);
}

char	*extract_path(char *cmd, char **envp , t_command **command_list)
{
	char	**path;
	char	*fullpath;
	int		i;

	i = 0;
	if (!command_list || !(*command_list))
		return (NULL);
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path && path[i])
	{
		fullpath = join_path(path[i], cmd);
		if (access(fullpath, X_OK) == 0)
		{
			free_split(path);
			return(fullpath);
		}
		free(fullpath);
		i++;
	}
	free_split(path);
	return (NULL);
}
