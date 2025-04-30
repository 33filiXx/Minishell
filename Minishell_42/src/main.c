/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:23:56 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/26 20:08:30 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../nrc/minishell.h"

void print_node (t_lexer *head)
{
    if(!head)
        return;
    while (head)
    {
        printf("%s : ->>>>>>>>>>>>> %u :\n" ,  head->content ,head->token);
        head = head->next;
    }
}


int main(int argc , char *argv[], char **envp)
{
    (void)argv;
    t_lexer *lexer;
    char *input;
    t_env *env;

    env = init_env(envp);
    lexer = (t_lexer *)malloc(sizeof(t_lexer));
    if (argc > 0)
    {
        while (1)
        {
            input = readline("minishell$ ");
            parsing(input , lexer);
            if (ft_strcmp(input, "ex") == 0)
                break;
            // if (*input)
            //     add_history(input);
            print_node(lexer);
            //ft_free_nodes(lexer);
            //printf("%s\n" , input);
        }
        //printf("%s", input);
    }

}