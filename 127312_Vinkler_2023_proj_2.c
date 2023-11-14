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

void free_lists(t_id_list **id_list, t_pozition_list **pozition_list, t_date_time_list **time_list, t_value_list **value_list, int data_count)
{
    //temporary pointers to node which will be deleted
    t_id_list *id_list_tmp;
    t_pozition_list *pozition_list_tmp;
    t_date_time_list *time_list_tmp;
    t_value_list *value_list_tmp;
    for (int i = 0; i < data_count; i++)
    {
        id_list_tmp = (*id_list);//save pointer to next node
        (*id_list) = (*id_list)->next;//move to next node
        free(id_list_tmp);//free node
        pozition_list_tmp = (*pozition_list);
        (*pozition_list) = (*pozition_list)->next;
        free(pozition_list_tmp);
        time_list_tmp = (*time_list);
        (*time_list) = (*time_list)->next;
        free(time_list_tmp);
        value_list_tmp = (*value_list);
        (*value_list) = (*value_list)->next;
        free(value_list_tmp);
    }
}

void data_load(char *char_name, t_id_list **id_list, t_pozition_list **pozition_list, t_date_time_list **date_time_list, t_value_list **value_list, int *data_count){
    FILE *fptr;
    fptr = fopen(char_name, "r");
    if (fptr == NULL)
    {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }
    if (*id_list != NULL)
    {
        free_lists(id_list, pozition_list, date_time_list, value_list, *data_count);
    }
    //create heads of linked lists
    *id_list = (t_id_list *)malloc(sizeof(t_id_list));
    *pozition_list = (t_pozition_list *)malloc(sizeof(t_pozition_list));
    *value_list = (t_value_list *)malloc(sizeof(t_value_list));
    *date_time_list = (t_date_time_list *)malloc(sizeof(t_date_time_list));
    (*date_time_list)->next = NULL;
    char datastorage[100];
    int line_count = 0;
    int node_count = 0;
    //load data to lists
    while (fscanf(fptr, "%s", datastorage) != -1)
    {
        if (datastorage[0] == '$')
        {
            node_count++;
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
            if (node_count == 0)
            {
                new_id_node->next = NULL;
            }else
            {
                new_id_node->next = (*id_list);
            }
            (*id_list) = new_id_node;
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
            if (node_count == 0)
            {
                new_pozition_node->next = NULL;
            }else
            {
                new_pozition_node->next = (*pozition_list);
            }
            (*pozition_list) = new_pozition_node;(*value_list);
            break;

        case 2:
            t_value_list *new_value_node = (t_value_list *)malloc(sizeof(t_value_list));
            new_value_node->unit[0] = datastorage[0];
            new_value_node->unit[1] = datastorage[1];
            fscanf(fptr, "%s", datastorage);
            new_value_node->value = atof(datastorage);
            if (node_count == 0)
            {
                new_value_node->next = NULL;
            }else
            {
                new_value_node->next = (*value_list);
            }
            (*value_list) = new_value_node;
            line_count++;
            break;

        case 4:
            t_date_time_list *new_date_time_node = (t_date_time_list *)malloc(sizeof(t_date_time_list));
            new_date_time_node->time = atoi(&datastorage[0]);
            fscanf(fptr, "%s", datastorage);
            new_date_time_node->date = atoi(datastorage);
            if (node_count == 0)
            {
                new_date_time_node->next = NULL;
            }else
            {
                new_date_time_node->next = (*date_time_list);
            }
            (*date_time_list) = new_date_time_node;
            break;
        }
        line_count++;
    }
    *data_count = node_count;
    printf("Nacitalo sa %d zaznamov\n", node_count);
    fclose(fptr);
}

void data_output(t_id_list *id_list, t_pozition_list *pozition_list, t_date_time_list *date_time_list, t_value_list *value_list, int data_count){
    if (data_count == 0)
    {
        return;
    }else
    {
        t_id_list *inverse_id_list = (t_id_list *)malloc(sizeof(t_id_list));
        t_value_list *inverse_value_list = (t_value_list *)malloc(sizeof(t_value_list));
        t_pozition_list *inverse_pozition_list = (t_pozition_list *)malloc(sizeof(t_pozition_list));
        t_date_time_list *inverse_date_time_list = (t_date_time_list *)malloc(sizeof(t_date_time_list));

        for (int i = 0; i < data_count; i++)
        {
            inverse_id_list->label[0] = id_list->label[0];
            inverse_id_list->type[0] = id_list->type[0];
            inverse_id_list->number = id_list->number;
            inverse_value_list->unit[0] = value_list->unit[0];
            inverse_value_list->unit[1] = value_list->unit[1];
            inverse_value_list->value = value_list->value;
            inverse_pozition_list->latitude = pozition_list->latitude;
            inverse_pozition_list->longitude = pozition_list->longitude;
            inverse_date_time_list->time = date_time_list->time;
            inverse_date_time_list->date = date_time_list->date;
            if (i == 0)
            {
                inverse_id_list->next = NULL;
                inverse_value_list->next = NULL;
                inverse_pozition_list->next = NULL;
                inverse_date_time_list->next = NULL;
            }else{
                t_id_list *id_list_tmp = (t_id_list *)malloc(sizeof(t_id_list));
                t_value_list *value_list_tmp = (t_value_list *)malloc(sizeof(t_value_list));
                t_pozition_list *pozition_list_tmp = (t_pozition_list *)malloc(sizeof(t_pozition_list));
                t_date_time_list *date_time_list_tmp = (t_date_time_list *)malloc(sizeof(t_date_time_list));
                //id_list
                id_list_tmp->next = inverse_id_list;
                inverse_id_list = id_list_tmp;
                id_list = id_list->next;
                //value_list
                value_list_tmp->next = inverse_value_list;
                inverse_value_list = value_list_tmp;
                value_list = value_list->next;
                //pozition_list
                pozition_list_tmp->next = inverse_pozition_list;
                inverse_pozition_list = pozition_list_tmp;
                pozition_list = pozition_list->next;
                //date_time_list
                date_time_list_tmp->next = inverse_date_time_list;
                inverse_date_time_list = date_time_list_tmp;
                date_time_list = date_time_list->next;
            }
            
        }
        for (int i = 0; i < data_count; i++)
        {
            printf("%d.\nID: %s%d%s\t%s\t%s\n", i+1,inverse_id_list->label, inverse_id_list->number, inverse_id_list->type, inverse_value_list->unit, inverse_value_list->value);
            printf("Poz: %.3lf\t%.3lf\n", inverse_pozition_list->latitude, inverse_pozition_list->longitude);
            printf("DaC: %d\t%d\n", inverse_date_time_list->date, inverse_date_time_list->time);
        }
        
    }
    
    
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