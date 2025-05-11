/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:23:56 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/05/11 20:03:34 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/minishell.h"

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
    (void)argc;
    (void)argv;
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
            if (args[1])
                set_env_value(&env, args[1], args[2] ? args[2] : "");
            else
                print_env(env);
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
    free_env(env);
    return 0;
}
