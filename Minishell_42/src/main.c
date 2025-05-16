/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:23:56 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/16 17:24:18 by wel-mjiy         ###   ########.fr       */
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

int main(int argc, char *argv[], char **envp)
{
    (void)argv;
    t_env *env;
    char *input;
    char **args;
    t_lexer *lexer;
    t_command *command = NULL;
    lexer = (t_lexer *)malloc(sizeof(t_lexer));
    command = (t_command *)malloc(sizeof(t_command));
    // Initialize environment
    env = init_env(envp);
    if (argc > 0)
    {
        
   
    while (1)
    {
        input = readline("minishell$ ");
        parsing(input , lexer);
        parser(lexer->next , &command);
        print_node(command->next);
        if (input == NULL)
            break; // Handle EOF or empty input
        if (*input) // Only add non-empty input
            add_history(input);
        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        args = ft_split(input, ' ');

        if (args[0] && ft_strcmp(args[0], "cd") == 0)
        {
            if (cd_builtin(env, args) != 0)
                fprintf(stderr, "cd: Error changing directory\n");
        }
        else if (args[0] && ft_strcmp(args[0], "pwd") == 0)
        {
            if (pwd_builtin(env) != 0)
                fprintf(stderr, "pwd: Error retrieving current directory\n");
        }
        else if (args[0] && ft_strcmp(args[0], "echo") == 0)
        {
            echo_builtin(args);
        }
        else if (args[0] && ft_strcmp(args[0], "env") == 0)
        {
            print_env(env);
        }
        else if (args[0] && ft_strcmp(args[0], "export") == 0)
        {
            export_builtin(&env, args);
        }
        else if (args[0] && ft_strcmp(args[0], "unset") == 0)
        {
            if (args[1])
                unset_env(&env, args[1]);
        }
        else if (args[0])
        {
            printf("Unknown command: %s\n", args[0]);
        }

        free(input);
        free_split(args);
    }
    write_history(".minishell_history");
    free_env(env);
    }
    return 0;
}
