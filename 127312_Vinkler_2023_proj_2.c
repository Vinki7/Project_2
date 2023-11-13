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
} t_id_list;//type definition

typedef struct pozition_list
{
    double latitude;
    double longitude;
    struct pozition_list *next;
} t_pozition_list;

typedef struct date_time_list
{
    int hour;
    int minute;
    int second;
    int day;
    int month;
    int year;
    struct time_list *next;
} t_time_list;

typedef struct value_list
{
    double value;
    char *unit;
    struct value_list *next;
} t_value_list;

void free_lists(t_id_list *id_list, t_pozition_list *pozition_list, t_time_list *time_list, t_value_list *value_list)
{
    t_id_list *ptr_id_list = id_list;
    t_pozition_list *ptr_pozition_list = pozition_list;
    t_time_list *ptr_time_list = time_list;
    t_value_list *ptr_value_list = value_list; 
    while (ptr_id_list != NULL)
    {
        free(ptr_id_list->label);
        free(ptr_id_list->type);
        id_list = id_list->next;
        free(ptr_id_list);
        ptr_id_list = id_list;
    }
    while (ptr_pozition_list != NULL)
    {
        pozition_list = pozition_list->next;
        free(ptr_pozition_list);
        ptr_pozition_list = pozition_list;
    }
    while (ptr_time_list != NULL)
    {
        time_list = time_list->next;
        free(ptr_time_list);
        ptr_time_list = time_list;
    }
    while (ptr_value_list != NULL)
    {
        value_list = value_list->next;
        free(ptr_value_list->unit);
        free(ptr_value_list);
        ptr_value_list = value_list;
    }
}

void data_load(char *file_name, t_id_list *id_list, t_pozition_list *pozition_list, t_time_list *time_list, t_value_list *value_list, int *data_count)
{
    FILE *fptr;
    fptr = fopen(file_name, "r");
    if (fptr == NULL)
    {
        printf("Subor sa nepodarilo otvorit\n");
        exit(1);
    }
    if (id_list != NULL)
    {
        free_lists(id_list, pozition_list, time_list, value_list);
    }
    
    char *datastorage = NULL;
    
    while ((scanf("%s", datastorage)  != -1))
    {
        printf("%s", datastorage);
    }
    fclose(fptr);
}

int main(void){
    printf("Zadajte príkaz:\n");
    char prikaz;
    t_id_list *ptr_id_list = NULL;
    t_pozition_list *ptr_pozition_list = NULL;
    t_time_list *ptr_time_list = NULL;
    t_value_list *ptr_value_list = NULL;
    int data_count = 0;
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