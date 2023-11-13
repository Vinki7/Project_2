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

typedef struct pozition_list
{
    double latitude;
    double longitude;
    struct pozition_list *next;
} pozition_list;

typedef struct date_time_list
{
    int hour;
    int minute;
    int second;
    int day;
    int month;
    int year;
    struct time_list *next;
} time_list;

typedef struct value_list
{
    double value;
    char *unit;
    struct value_list *next;
} value_list;

void new_lists(id_list *id_list, pozition_list *pozition_list, time_list *time_list, value_list *value_list)
{
    id_list->label = NULL;
    id_list->number = 0;
    id_list->type = NULL;
    id_list->next = NULL;

    pozition_list->latitude = 0;
    pozition_list->longitude = 0;
    pozition_list->next = NULL;

    time_list->hour = 0;
    time_list->minute = 0;
    time_list->second = 0;
    time_list->day = 0;
    time_list->month = 0;
    time_list->year = 0;
    time_list->next = NULL;

    value_list->value = 0;
    value_list->unit = NULL;
    value_list->next = NULL;
}

void data_load(char *file_name, id_list *id_list, pozition_list *pozition_list, time_list *time_list, value_list *value_list, int *data_count)
{
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Subor sa nepodarilo otvorit\n");
        exit(1);
    }
    if ((id_list->label)!=NULL)
    {

    }
    
    char *datastorage = NULL;
    
    while ((scanf("%s", datastorage)  != -1))
    {
        printf("%s", datastorage);
    }
    fclose(file);
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