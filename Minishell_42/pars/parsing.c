/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:12:47 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/15 17:32:18 by wel-mjiy         ###   ########.fr       */
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
	int		j;
	char	**new_str;

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

void check_helper_one(t_lexer *lexer)
{
	printf("bash: syntax error near unexpected token `newline'\n");
	ft_free_nodes(lexer);
	exit(1);
}
int herdoc_counter(char *str)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while(str[i])
	{
		if(str[i] == '<')
		{
			counter += 1;
		}
		else
			return counter;
		i++;
	}
	return counter;
}
int append_counter(char *str)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while(str[i])
	{
		if(str[i] == '>')
		{
			counter += 1;
		}
		else
			return counter;
		i++;
	}
	return counter;
}
int pipe_counter(char *str)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while(str[i])
	{
		if(str[i] == '|')
		{
			counter += 1;
		}
		else
			return counter;
		i++;
	}
	return counter;
}
void check_append(t_lexer *lexer)
{
	char *str;
	int i;

	i = 0;
	if (lexer == NULL)
		return;
	while (lexer)
	{
		str = lexer->content;
		if (str[i] == '>')
		{
			if(append_counter(str) == 3)
			{
				printf("bash: syntax error near unexpected token `>'\n");
				ft_free_nodes(lexer);
				exit(1);
			}
			else if (append_counter(str) >= 4)
			{
				printf("bash: syntax error near unexpected token `>>'\n");
				ft_free_nodes(lexer);
				exit(1);
			}
			else
				return;
		}
		lexer = lexer->next;
	}
}
void check_herdoc(t_lexer *lexer)
{
	char *str;
	int i;

	i = 0;
	if (lexer == NULL)
		return;
	while (lexer)
	{
		str = lexer->content;
		if (str[i] == '<')
		{
			if(herdoc_counter(str) == 3)
				check_helper_one(lexer);
			else if (herdoc_counter(str) == 4)
			{
				printf("bash: syntax error near unexpected token `<'\n");
				ft_free_nodes(lexer);
				exit(1);
			}
			else if (herdoc_counter(str) == 5)
			{
				printf("bash: syntax error near unexpected token `<<'\n");
				ft_free_nodes(lexer);
				exit(1);
			}
			else if (herdoc_counter(str) >= 6)
			{
				printf("bash: syntax error near unexpected token `<<<'\n");
				ft_free_nodes(lexer);
				exit(1);
			}
			else
				return;
		}
		lexer = lexer->next;
	}
}
void check_pipe(t_lexer *lexer)
{
	char *str;
	int i;

	i = 0;
	if (lexer == NULL)
		return;
	while (lexer)
	{
		str = lexer->content;
		if (str[i] == '|')
		{
			if(pipe_counter(str) == 3)
			{
				printf("bash: syntax error near unexpected token `|'\n");
				ft_free_nodes(lexer);
				exit(1);
			}
			else if (pipe_counter(str) >= 4)
			{
				printf("bash: syntax error near unexpected token `||'\n");
				ft_free_nodes(lexer);
				exit(1);
			}
			else
				return;
		}
		lexer = lexer->next;
	}
}



void check_ifonly_op(t_lexer *lexer)
{
	if (!lexer)
	{
		return;
	}
	t_lexer *tmp = lexer->next;
	char *str = lexer->content;
	if(strcmp(lexer->content , "<<") == 0 && tmp == NULL)
	{
		check_helper_one(lexer);
	}
	else if(strcmp(lexer->content , ">>") == 0  && tmp == NULL)
	{
		check_helper_one(lexer);
	}
	else if(strcmp(lexer->content , ">") == 0 && tmp == NULL)
		check_helper_one(lexer);
	else if(strcmp(lexer->content , "<") == 0 && tmp == NULL)
		check_helper_one(lexer);
	else if((strcmp(lexer->content , "|") == 0 || strcmp(lexer->content , "|") != 0) && tmp == NULL)
	{
		if (pipe_counter(str) == 1)
		{
			printf("bash: syntax error near unexpected token `|'\n");
			ft_free_nodes(lexer);
			exit(1);
		}
		else if (pipe_counter(str) > 1)
		{
			printf("bash: syntax error near unexpected token `||'\n");
			ft_free_nodes(lexer);
			exit(1);
		}
	}
}
void	parsing(char *argv, t_lexer *lexer)
{
	
	store_into_nodes(argv, lexer);	
	check_ifonly_op(lexer->next);
	//check_herdoc(lexer->next);
	//check_append(lexer->next);
	//check_pipe(lexer->next);
}