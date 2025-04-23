#include "../nrc/minishell.h"

void print_node (t_lexer *head)
{
    if(!head)
        return;
    while (head)
    {
        printf("%s : ->>>>>>>>>>>>> %u :\n" , head->content , head->token);
        head = head->next;
    }
}


int main(int argc , char *argv[])
{
    t_lexer *lexer;
    lexer = (t_lexer *)malloc(sizeof(t_lexer));
    if (argc >= 1)
    {
        parsing(argv , lexer);
        print_node(lexer);
    }

}