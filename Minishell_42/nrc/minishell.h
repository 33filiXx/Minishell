#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../ft_libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


typedef struct s_data
{
	void			*contnet;
	struct s_data	*next;

} t_data;

t_data *creat_node(void *content);
void add_front(t_data **head , void *content);
void	insert_at_end(t_data **head, void *content);

#endif