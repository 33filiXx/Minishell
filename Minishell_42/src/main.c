/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:23:56 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:18:17 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"

<<<<<<< HEAD
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
=======
void free_env(t_env *env)
>>>>>>> yassir
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

<<<<<<< HEAD
int main(int argc , char *argv[])
=======
int main(int argc, char *argv[], char **envp)
>>>>>>> yassir
{
    (void)argc;
    (void)argv;
<<<<<<< HEAD
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
=======
    t_env *env;
    char *input;
    char **args;

    // Initialize environment
    env = init_env(envp);

    while (1)
    {
        input = readline("minishell$ ");
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
    return 0;
}
>>>>>>> yassir
