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