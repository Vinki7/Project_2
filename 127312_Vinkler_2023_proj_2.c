#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linked list for write
typedef struct id_list//structure definition
{
    char *label;
    int number;
    char *type;  
    struct id_list *next;//pointer to next element (node)
} id_list;//type definition





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