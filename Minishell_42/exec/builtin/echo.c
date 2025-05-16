/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:50:26 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/05/16 17:18:58 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../nrc/minishell.h"

// echo hello world      # prints: hello world\n
// echo -n hello world   # prints: hello world
// echo -nnnn hello      # still suppresses newline (Bash-compatible)

int	is_flag(char *arg)
{
	int	i;

	i = 0;
	if (!arg || arg[0] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_builtin(char **args)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = 1;
	while(args[i] && is_flag(args[i]))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
