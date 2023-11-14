#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linked list for write
typedef struct id_list//structure definition
{
    char label[2];
    int number;
    char type[2];  
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
    int time;
    int date;
    struct date_time_list *next;
} t_date_time_list;

typedef struct value_list
{
    double value;
    char unit[3];
    struct value_list *next;
} t_value_list;

void free_lists(t_id_list *id_list, t_pozition_list *pozition_list, t_date_time_list *time_list, t_value_list *value_list)
{
    t_id_list *ptr_id_list = id_list;
    t_pozition_list *ptr_pozition_list = pozition_list;
    t_date_time_list *ptr_time_list = time_list;
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

void data_load(char *char_name, t_id_list **id_list, t_pozition_list **pozition_list, t_date_time_list **time_list, t_value_list **value_list, int *data_count){
    FILE *fptr;
    fptr = fopen(char_name, "r");
    if (fptr == NULL)
    {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }
    if (*id_list != NULL)
    {
        free_lists(*id_list, *pozition_list, *time_list, *value_list);
    }
    //create heads of linked lists
    t_id_list *head_id_node = (t_id_list *)malloc(sizeof(t_id_list));
    t_pozition_list *head_pozition_node = (t_pozition_list *)malloc(sizeof(t_pozition_list));
    t_value_list *head_value_node = (t_value_list *)malloc(sizeof(t_value_list));
    t_date_time_list *head_time_node = (t_date_time_list *)malloc(sizeof(t_date_time_list));
    char datastorage[100];
    int line_count = 0;
    //load data to lists
    while (fscanf(fptr, "%s", datastorage) != -1)
    {
        if (datastorage[0] == '$')
        {
            data_count++;
            fscanf(fptr, "%s", datastorage);
            line_count = 0;
        }
        switch (line_count)
        {
        case 0:
            t_id_list *new_id_node = (t_id_list *)malloc(sizeof(t_id_list));
            new_id_node->label[0] = datastorage[0];
            new_id_node->type[0] = datastorage[4];
            new_id_node->number = atoi(&datastorage[1]);
            new_id_node->next = head_id_node;
            head_id_node = new_id_node;
            break;
        
        case 1:
            t_pozition_list *new_pozition_node = (t_pozition_list *)malloc(sizeof(t_pozition_list));
            new_pozition_node->latitude = atof(&datastorage[1]);
            if (datastorage[0] == '-')
            {
                new_pozition_node->latitude *= -1;
            }
            new_pozition_node->longitude = atof(&datastorage[9]);
            if (datastorage[8] == '-')
            {
                new_pozition_node->longitude *= -1;
            }
            new_pozition_node->next = head_pozition_node;
            head_pozition_node = new_pozition_node;
            break;
            
        default:
            break;
        }
        line_count++;
    }
    fclose(fptr);
}

int main(void){
    printf("Zadajte príkaz:\n");
    char prikaz;
    t_id_list *head_id_list = NULL;
    t_pozition_list *head_pozition_list = NULL;
    t_date_time_list *head_time_list = NULL;
    t_value_list *head_value_list = NULL;
    int data_count = 0;
    while (1)
    {
        scanf(" %c", &prikaz);
        switch (prikaz)
        {
        case 'v':
            
            break;
        
        case 'n':
            data_load("dataloger_V2.txt", &head_id_list, &head_pozition_list, &head_time_list, &head_value_list, &data_count);
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