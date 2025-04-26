/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:12:47 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/24 18:44:11 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
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

void	store_into_nodes(char *str, t_lexer *lexer)
{
	//int		i;
	int		j;
	//int		p;
	char	**new_str;

	//i = 1;
	//p = 0;
	new_str = ft_split(str, ' ');
	j = 0;
	while (new_str[j] != NULL)
	{
			if (ft_strcmp(new_str[j], "|") == 0)
				insert_at_end(&lexer, new_str[j], PIPE);
			else if (ft_strcmp(new_str[j], ">") == 0)
				insert_at_end(&lexer, new_str[j], TRUNC);
			else if (ft_strcmp(new_str[j], "<") == 0)
				insert_at_end(&lexer, new_str[j], INPUT);
			else if (ft_strcmp(new_str[j], ">>") == 0)
				insert_at_end(&lexer, new_str[j], APPEND);
			else if (ft_strcmp(new_str[j], "<<") == 0)
				insert_at_end(&lexer, new_str[j], HERDOC);
			else
				insert_at_end(&lexer, new_str[j], WORD);
			//	free(*new_str);
			j++;
	}
}

void	parsing(char *argv, t_lexer *lexer)
{
	
	store_into_nodes(argv, lexer);
}