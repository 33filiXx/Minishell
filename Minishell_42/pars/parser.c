/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:09:58 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/16 20:14:09 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"

t_command	*new_command_node(void)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->argv = NULL;   // still empty, ghadi t-allociha mn b3d
	node->redirs = NULL; // redirection list, bda f NULL
	node->pipe_in = 1;   // default: no input pipe
	node->pipe_out = 0;  // default: no output pipe
	node->next = NULL;   // no next command yet
	return (node);
}
void	add_command_back(t_command **head, t_command *new)
{
	t_command	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
void add_redir_back(t_redirection **head, t_redirection *new)
{
    if (!*head)
        *head = new;
    else
    {
        t_redirection *tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

int found_pipe(t_lexer *lexer)
{
	if (!lexer)
		return 1;
	int check = 0;
	while (lexer)
	{
		if (lexer->token == PIPE)
		{
			check = 1;
			return check;
		}
		lexer = lexer->next;
	}
	return check;
}

void	parser(t_lexer *lexer, t_command **command_list)
{
	int				i;
	int				check_pipe;
	t_command		*command;
	t_redirection	*redir;

	i = 0;
	check_pipe = 0;
	int check_out = 0;
	int check_file = 0;
	while (lexer)
	{
		command = new_command_node();
		command->argv = malloc(sizeof(char *) * 100);
        if (!command->argv)
            return;
		if (found_pipe(lexer) == 0 && check_out == 0)
		{
			command->pipe_in = 0;
			command->pipe_out = 0;
			check_out = 1;
		}
		else
			check_out = 1;
		
        i = 0;
		while (lexer && lexer->token == WORD)
		{
			command->argv[i] = ft_strdup(lexer->content);
			i++;
			lexer = lexer->next;
		}
		command->argv[i] = NULL;
		while (lexer && (lexer->token == HERDOC || lexer->token == TRUNC
			|| lexer->token == INPUT || lexer->token == APPEND))
		{
            if (!lexer && !lexer->next)  // a zbi
            {
		        break;
            }
			redir = malloc(sizeof(t_redirection));
            if(!redir)
            {
                return;
            }
			redir->filename = ft_strdup(lexer->next->content); // y9der ykoon bzaaf dyal redirections
			redir->next = NULL;
			if (lexer->token == TRUNC)
				redir->type = REDIR_OUT;
			else if (lexer->token == HERDOC)
				redir->type = HEREDOC;
			else if (lexer->token == APPEND)
				redir->type = REDIR_APPEND;
			else if (lexer->token == INPUT)
				redir->type = REDIR_IN;
            add_redir_back(&command->redirs , redir);
            lexer = lexer->next;
            if( lexer && lexer->next && lexer->token == WORD  && lexer->next->token != WORD)
                lexer = lexer->next;
			else if (!lexer->next)
				return;
		}
		while (lexer && lexer->token == WORD)
		{
			if (check_file == 0)
			{
				lexer = lexer->next;
				check_file = 1; 
			}
			command->argv[i] = ft_strdup(lexer->content);
			i++;
			lexer = lexer->next;
		}
		if (lexer && lexer->token == PIPE)
		{
			if (check_pipe == 0)
			{
				command->pipe_in = 0;
				command->pipe_out = 1;
				check_pipe = 1;
			}
			else if (check_pipe != 0)
			{
				command->pipe_in = 1;
				command->pipe_out = 1;
			}
		    lexer = lexer->next;
		}
		add_command_back(command_list, command);
	}
}
