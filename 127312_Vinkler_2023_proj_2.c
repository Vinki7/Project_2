#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linked list for write
typedef struct write_list//structure definition
{
    char *id;
    char *pozition;
    char *dimension;
    int value;
    int date;
    int time;
    struct write_list *next;//pointer to next element (node)
} write_list_t;//type definition


void n(FILE *fptr, char *id, char *pozition, char *dimension, int value, int date, int time, write_list_t *head)
{   //function for adding new element to linked list
    char datastorage[100];//string for storing data from file, buffer = 100 characters
    if (head != NULL)
    {
        //free memory stored in write_list_t
        write_list_t *current = head;//pointer to current element (node)
        while (current != NULL)
        {
            write_list_t *next = current->next;//pointer to next element (node)
            free(current);
            current = next;
        }
    }
    head = NULL;
    write_list_t *new_node = malloc(sizeof(write_list_t));//allocating memory for new element
    if (new_node == NULL)//check if memory was allocated properly
    {
        printf("Error allocating memory\n");
        exit(1);//if not, end program
    }
}
int main(void){
    printf("Zadajte príkaz:\n");
    char prikaz;
    while (1)
    {
        scanf(" %c", &prikaz);
        switch (prikaz)
        {
        case 'v':
            
            break;
        
        case 'n':
            
            break;

        case 'c':
            
            break;

        case 's':
            
            break;

        case 'h':
            
            break;
        
        case 'z':
            
            break;
        
        case 'k':
            
            break;
        default:
            printf("Zadali ste nedefinovaný príkaz, skúste to prosím znovu...\n");
        }
        printf("Zadajte ďalší príkaz...\n");
    }
    return 0;
}