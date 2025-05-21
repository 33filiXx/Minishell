/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:23:56 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/21 18:10:46 by wel-mjiy         ###   ########.fr       */
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
        printf("%s : ->>>>>>>>>>>>> %u ->>>>>>>>>>>>>>>>>>>>>>> %u :\n" ,  head->content ,head->token , head->quotes);
        head = head->next;
    }
}

int *exit_stat(void)
{
    static int stat;

    return(&stat);
}

// Function to create a mock command
// t_command *create_mock_command()
// {
//     // First command: ls
//     t_command *cmd1 = malloc(sizeof(t_command));
//     cmd1->argv = malloc(sizeof(char *) * 2);
//     cmd1->argv[0] = strdup("ls");
//     cmd1->argv[1] = NULL;
//     cmd1->redirs = NULL;
//     cmd1->path = ft_strdup("/bin/ls");
//     cmd1->pipe_in = 0;     // No pipe into first command
//     cmd1->pipe_out = 1;    // Pipe output to next
//     cmd1->next = NULL;

//     // Second command: grep minishell
//     t_command *cmd2 = malloc(sizeof(t_command));
//     cmd2->argv = malloc(sizeof(char *) * 3);
//     cmd2->argv[0] = strdup("grep");
//     cmd2->argv[1] = strdup("minishell");
//     cmd2->argv[2] = NULL;
//     cmd2->redirs = NULL;
//     cmd2->path = ft_strdup("/bin/grep");
//     cmd2->pipe_in = 1;     // Receive input from previous command
//     cmd2->pipe_out = 0;    // No pipe out
//     cmd2->next = NULL;

//     // Link commands
//     cmd1->next = cmd2;

//     return cmd1;
// }

int main(int argc, char *argv[], char **envp)
{
    (void)argv;
    (void)argc;
    t_env *env;
    char *input;
    t_lexer *lexer_list = NULL;
    t_command *command = NULL;
    env = init_env(envp);
    //int i = 0;
    if (argc > 0)
    {
        
    while (1)
    {
        input = readline("minishell$ ");
        lexer(input , &lexer_list);
        //expand(env , &lexer_list);
        //parser(lexer_list, &command ,  list_to_char_array(env));
        //  print_node(command);
        //print_nodee(lexer_list);
        if (input == NULL)
            break; // Handle EOF or empty input
        if (*input) // Only add non-empty input
            add_history(input);
        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        if (command && (command->pipe_in || command->pipe_out))
            execute_pipeline(command, env);
        else
            init_exc(command, env);
        if (command)
        {
            free_commend(command);
            command = NULL;
        }
        free(input);
    }
    write_history(".minishell_history");
    free_env(env);
    }
    //command = create_mock_command();
    return *exit_stat();
}
 