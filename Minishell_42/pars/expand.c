/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:58:56 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/21 18:08:53 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"

void expand(t_env *env , t_lexer **lexer)
{ 
    t_lexer *tmp = *lexer;
    int i = 0;
    while (tmp)
    {
        if(tmp->token == WORD && tmp->quotes == non_quotes)
        {
            if (tmp->content[i] == '$')
            {                
                while (env)
                {
                    if (strcmp(tmp->content[i + 1] , env->key) == 0)
                        break;
                    env = env->next;
                }
                            
            }
        }
        tmp = tmp->next;
    }
    
}