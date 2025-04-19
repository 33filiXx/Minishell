#include "../nrc/minishell.h"

// void print_node (t_data *head)
// {
//     if(!head)
//         return;
//     while (head)
//     {
        
//     }
    
// }


int main()
{
    t_data *head = NULL;
    int *num = malloc(sizeof(int));
    *num = -1;
    add_front(&head , "walid");
    add_front(&head , num);
    printf("%d" , *(int *)head->contnet);
    
}