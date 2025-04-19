/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:12:33 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/19 17:05:38 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"


t_data *creat_node(void *content)
{
    t_data *new_node ;

    new_node = (t_data *)malloc(sizeof(t_data));
    if(!new_node)
    {
        free(new_node);
        return NULL;
    }
    new_node->contnet = content;
    new_node->next = NULL;
    return (new_node);
}

void add_front(t_data **head , void *content)
{
    t_data *new_node;
    t_data *tmp;

    new_node = creat_node(content);
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    tmp = *head;
    *head = new_node;
    new_node->next = tmp;    
}
void	insert_at_end(t_data **head, void *content)
{
	t_data	*new_node;
	t_data	*temp;

	new_node = creat_node(content);
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