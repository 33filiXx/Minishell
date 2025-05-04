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


int main(int argc , char *argv[])
{
    (void)argv;
    t_lexer *lexer;
    char *input;
    lexer = (t_lexer *)malloc(sizeof(t_lexer));
    if (argc > 0)
    {
        while (1)
        {
            input = readline("minishell$ ");
            parsing(input , lexer);
            if (ft_strcmp(input, "exit") == 0)
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