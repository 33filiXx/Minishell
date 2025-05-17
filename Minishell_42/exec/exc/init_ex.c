/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:37:35 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/17 20:39:20 by ykhoussi         ###   ########.fr       */
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
            return (unset_env(&env, cmd->argv[1]), 0);
        else
            fprintf(stderr, "unset: not enough arguments\n");
    }
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		    return (print_env(env), 0);
    else
		{execve(cmd->path, cmd->argv, list_to_char_array(env));
		}
			return 0;
	
}
