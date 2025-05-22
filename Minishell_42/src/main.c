/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:23:56 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/22 15:52:37 by ykhoussi         ###   ########.fr       */
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

void sigint_handler(int signo)
{
    (void)signo;
    write(1, "\n", 1);
}

        // print_node(command);
        // print_nodee(lexer_list);
int main(int argc, char *argv[], char **envp)
{
    (void)argv;
    (void)argc;

    t_env *env = init_env(envp);
    char *input;
    t_lexer *lexer_list = NULL;
    t_command *command = NULL;

    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            ctrl_d_handle();
        if (*input)
            add_history(input);
        lexer(input, &lexer_list);
        char **env_char = list_to_char_array(env);
        parser(lexer_list, &command, env_char);
        free_split(env_char);
        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        if (command)
        {
            if (command->pipe_in || command->pipe_out)
                execute_pipeline(command, env);
            else
                init_exc(command, env);
            free_commend(command);
            command = NULL;
        }
        // free_lexer(lexer_list);
        lexer_list = NULL;
        free(input);
    }
    write_history(".minishell_history");
    free_env(env);
    return *exit_stat();
}
