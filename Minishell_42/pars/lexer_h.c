/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:12:33 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/16 20:14:31 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"

t_lexer *creat_node(char *content  , e_tokens token)
{
    t_lexer *new_node ;

    new_node = (t_lexer *)malloc(sizeof(t_lexer));
    if(!new_node)
    {
        // free(new_node);  feker fiha w hyedha
        return NULL; 
    }
	new_node->token = token;	
    new_node->content = ft_strdup(content);
    new_node->next = NULL;
    return (new_node);
}
void	insert_at_end(t_lexer **head, char *content ,e_tokens token)
{
	t_lexer	*new_node;
	t_lexer	*temp;

	new_node = creat_node(content , token);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new_node;
}

void ft_free_nodes(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer != NULL)
	{
		tmp = lexer->next;
		free(lexer);
		lexer = tmp;
	}
	//lexer = NULL;
}
