/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:58:56 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/21 18:29:48 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"

void expand(t_env *env , t_lexer **lexer)
{ 
    t_lexer *tmp = *lexer;
    int check = 0;
    int i = 0;
    while (tmp)
    {
        if(tmp->token == WORD && tmp->quotes == non_quotes)
        {
            if (tmp->content[i] == '$')
            {                
                while (env)
                {
                    if (ft_strcmp(&tmp->content[i + 1] , env->key) == 0)
                    {
                        check = 1;
                        break;
                    }
                    env = env->next;
                }
                if (check == 1)
                    tmp->content = ft_strdup(env->value);
            }
        }
        else if (tmp->token == WORD && tmp->quotes == double_quotes)
        {
            
        }
        tmp = tmp->next;
    }
    
}