/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:12:47 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/23 10:52:16 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"

void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	store_into_nodes(char **str , t_lexer *lexer)
{
	int		i;
	int		j;
	int		p;
	char	**new_str;

	i = 1;
	p = 0;
	while (str[i] != NULL)
	{
		new_str = ft_split(str[i], ' ');
		j = 0;
		while (new_str[j] != NULL)
		{
			if (new_str[j][p] == '|')
				insert_at_end(&lexer , new_str[j] , PIPE);
			if (new_str[j][p] == '>')
				insert_at_end(&lexer , new_str[j] , TRUNC);
			if (new_str[j][p] == '<')
				insert_at_end(&lexer , new_str[j] , INPUT);
			if (new_str[j][p] == '>' && new_str[j][p + 1] == '>')
				insert_at_end(&lexer , new_str[j] , APPEND);
			if (new_str[j][p] == '<' && new_str[j][p + 1] == '<')
				insert_at_end(&lexer , new_str[j] , HERDOC);
			else
				insert_at_end(&lexer , new_str[j] , WORD);
		//	free(*new_str);
			j++;
		}
		i++;
	}
}

void	parsing(char **argv , t_lexer *lexer)
{
	store_into_nodes(argv , lexer);
}