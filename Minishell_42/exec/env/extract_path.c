/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:02:00 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/19 14:33:50 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

// static	char	*get_command_path(char **cmd, char **envp, t_command **command_list)
// {
// 	char	*expath;

// 	if (cmd && ft_strchr(cmd[0], '/'))
// 	{
// 		expath = ft_strdup(cmd[0]);
// 		if (!expath)
// 			return (NULL);
// 	}
// 	else
// 		expath = extract_path(cmd[0], envp, command_list);
// 	return (expath);
// }

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

void	extract_path(char *cmd, char **envp , t_command **command_list)
{
	char	**path;
	char	*fullpath;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return;
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path && path[i])
	{
		fullpath = join_path(path[i], cmd);
		if (access(fullpath, X_OK) == 0)
		{
			free_split(path);
			(*command_list)->path = ft_strdup(fullpath);
		}
		free(fullpath);
		i++;
	}
	free_split(path);
}
