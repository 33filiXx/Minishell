/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:45:59 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/04/24 22:03:43 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

int pwd_builtin(void)
{
    char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if(!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
