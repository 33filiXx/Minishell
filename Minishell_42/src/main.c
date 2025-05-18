/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:23:56 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/18 20:31:31 by ykhoussi         ###   ########.fr       */
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
        printf("path: %s\n----------------",head->path);
        
        // Print pipe info
        printf("pipe_in: %d, pipe_out: %d\n", head->pipe_in, head->pipe_out);

        printf("----------------------------------------------------------------------------------------\n\n\n");

        head = head->next;
    }
}


void free_env(t_env *env)
{
    t_env *temp;

    while (env)
    {
        temp = env;
        env = env->next;
        free(temp->key);   // Free the key string
        free(temp->value); // Free the value string
        free(temp);        // Free the node itself
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

int *exit_stat(void)
{
    static int stat;

    return(&stat);
}

// Function to create a mock command
t_command *create_mock_command()
{
    t_command *cmd = malloc(sizeof(t_command));
    cmd->argv = malloc(sizeof(char *) * 2);
    cmd->argv[0] = strdup("ls");
    cmd->argv[1] = NULL;
    cmd->redirs = NULL;
    cmd->path = strdup("");
    cmd->pipe_in = 0;
    cmd->pipe_out = 0;
    cmd->next = NULL;

    return cmd;
}

int main(int argc, char *argv[], char **envp)
{
    (void)argv;
    (void)argc;
    t_env *env;
    // char *input;
    // t_lexer *lexer = NULL;
    t_command *command = NULL;
    env = init_env(envp);
    // int i = 0;
    // if (argc > 0)
    // {
        
    // while (1)
    // {
    //     input = readline("minishell$ ");
    //     parsing(input , &lexer);
    //     parser(lexer, &command);
    //     while (command)
    //     {
    //         while (command->argv[i])
    //         {
    //         if (command->argv[0])
	// 		    extract_path(command->argv[0], envp, &command);
    //             i++;
    //         }
    //         command = command->next;
    //     }
        
    
    //     print_node(command);
    //     // print_nodee(lexer);
    //     if (input == NULL)
    //         break; // Handle EOF or empty input
    //     if (*input) // Only add non-empty input
    //         add_history(input);
    //     if (ft_strcmp(input, "exit") == 0)
    //     {
    //         free(input);
    //         break;
    //     }
    //     init_exc(command, env);
    //     if (command)
    //     {
    //         free_commend(command);
    //         command = NULL;
    //     }
    //     free(input);
    // }
    // write_history(".minishell_history");
    // free_env(env);
    // }
    command = create_mock_command();
    init_exc(command, env);
    return 0;
}
 