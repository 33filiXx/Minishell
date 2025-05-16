/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:23:56 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/26 08:23:57 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../nrc/minishell.h"

void print_node(t_command *head)
{
    while (head)
    {
        printf("----- Command Node -----\n");

        // Print argv
        int i = 0;
        while (head->argv && head->argv[i])
        {
            printf("argv[%d] = [%s]\n", i, head->argv[i]);
            i++;
        }

        // Print redirections (use a temp pointer so we don't lose original list)
        t_redirection *redir = head->redirs;
        while (redir)
        {
            int type = redir->type;
            char *smiyadyaltype = NULL;
            switch (type)
            {   
            case 1:
                smiyadyaltype = "REDIR_IN";
                break;
            case 2:
                smiyadyaltype = "REDIR_OUT";
                break;
            case 3:
                smiyadyaltype = "REDIR_APPEND";
                break;
            case 4:
                smiyadyaltype = "HEREDOC";
                break;
            default:
                break;
            }
            printf("redir: { type: %s, filename: %s }\n", smiyadyaltype, redir->filename);
            redir = redir->next;
        }

        // Print pipe info
        printf("pipe_in: %d, pipe_out: %d\n", head->pipe_in, head->pipe_out);

        printf("----------------------------------------------------------------------------------------\n\n\n");

        head = head->next;
    }
}


void print_nodee (t_lexer *head)
{
    if(!head)
        return;
    while (head)
    {
        printf("%s : ->>>>>>>>>>>>> %u :\n" ,  head->content ,head->token);
        head = head->next;
    }
}

int main(int argc , char *argv[])
{
    (void)argv;
    t_lexer *lexer;
    t_command *command = NULL;
    char *input;
    lexer = (t_lexer *)malloc(sizeof(t_lexer));
    command = (t_command *)malloc(sizeof(t_command));
    if (argc > 0)
    {
        while (1)
        {
            input = readline("minishell$ ");
            parsing(input , lexer);
            parser(lexer->next , &command);
            if (ft_strcmp(input, "exit") == 0)
                break;
            // if (*input)
            //     add_history(input);
            print_node(command->next);
            //print_nodee(lexer->next);
            
            //ft_free_nodes(lexer);
            //printf("%s\n" , input);
        }
        //printf("%s", input);
    }

}  