/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:12:47 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/19 19:01:01 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"

void store_into_nodes(char **str)
{
    int i;
    int j;
    char **new_str;
    t_lexer lexer;

    i = 0;
    new_str = ft_split(str , ' ');
    while (new_str[i] != NULL)
    {
        j = 0;
        while (new_str[i][j] != '\0')
        {
            
            j++;
        }
        i++;
    }
    
}



void parsing(char **argv)
{
    store_into_nodes(argv);       
}