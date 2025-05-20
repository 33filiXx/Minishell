/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:02:00 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/20 04:54:00 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

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
	if (!command_list || !(*command_list))
		return;
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
			(*command_list)->path = ft_strdup(fullpath);
			free(fullpath);
			free_split(path);
			return;
			//printf("%s\n", fullpath);
			// if (*command_list)
		}
		free(fullpath);
		i++;
	}
	free_split(path);
}
