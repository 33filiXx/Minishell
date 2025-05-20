/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:12:47 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/20 10:45:24 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
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
int checkquotes(char *str)
{
	if (!str)
		return 0;
	int i = 0;
	int single_cheker = 0;
	int double_cheker = 0;
	while(str[i])
	{
		if (str[i] == '"')
			double_cheker += 1;
		else if (str[i] == '\'')
			single_cheker += 1;
		i++;
	}
	
	if (single_cheker % 2 != 0 && double_cheker % 2 == 0)
		return 4;
	else if (single_cheker % 2 == 0 && double_cheker % 2 != 0)
		return 5;
	else if (single_cheker % 2 != 0 && double_cheker % 2 != 0)
		return 6;
	else if (single_cheker > 0 && double_cheker == 0)
		return 0;
	else if (double_cheker > 0 && single_cheker == 0)
		return 1;
	else if (single_cheker > 0 && double_cheker > 0)
		return 2;
	else if ( single_cheker == 0 && double_cheker == 0)
		return 3;
	return 7;
}
void	store_into_nodes(char *str, t_lexer **lexer)
{
	int		j;
	char	**new_str;

	new_str = ft_split(str, ' ');
	j = 0;
	while (new_str[j] != NULL)
	{
			if (ft_strcmp(new_str[j], "|") == 0)
				insert_at_end(lexer, new_str[j], PIPE ,3);
			else if (ft_strcmp(new_str[j], ">") == 0)
				insert_at_end(lexer, new_str[j], TRUNC,3);
			else if (ft_strcmp(new_str[j], "<") == 0)
				insert_at_end(lexer, new_str[j], INPUT,3);
			else if (ft_strcmp(new_str[j], ">>") == 0)
				insert_at_end(lexer, new_str[j], APPEND,3);
			else if (ft_strcmp(new_str[j], "<<") == 0)
				insert_at_end(lexer, new_str[j], HERDOC,3);
			else
			{
				if(checkquotes(new_str[j]) == 0)
					insert_at_end(lexer, new_str[j], WORD , 0);
				else if (checkquotes(new_str[j]) == 1)
					insert_at_end(lexer, new_str[j], WORD , 1);
				else if (checkquotes(new_str[j]) == 2)
					insert_at_end(lexer, new_str[j], WORD , 2);
				else if (checkquotes(new_str[j]) == 3)
					insert_at_end(lexer, new_str[j], WORD , 3);
				else if (checkquotes(new_str[j]) == 4)
					insert_at_end(lexer, new_str[j], WORD , 4);
				else if (checkquotes(new_str[j]) == 5)
					insert_at_end(lexer, new_str[j], WORD , 5);
				else if (checkquotes(new_str[j]) == 6)
					insert_at_end(lexer, new_str[j], WORD , 6);
			}
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
void	lexer(char *argv, t_lexer **lexer)
{
	*lexer = NULL;
	store_into_nodes(argv, lexer);	
	//check_ifonly_op(lexer->next);
	//check_herdoc(lexer->next);
	//check_append(lexer->next);
	//check_pipe(lexer->next);
}
