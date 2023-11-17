//Šimon Vinkler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linked list structures
typedef struct id_list//structure definition
{
    char label[2];
    int number;
    char type[2];  
} t_id_list;//type definition

typedef struct pozition_list
{
    char operator_lat[2];
    double latitude;
    char operator_long[2];
    double longitude;
} t_pozition_list;

typedef struct data_log
{
    t_id_list *id;
    t_pozition_list *pozition;
    int date;
    int time;
    double value;
    char unit[3];
    struct data_log *next;
} t_data_log;

void free_lists(t_data_log **head_datalog, int data_count){
    //temporary pointers to node which will be deleted
    t_data_log *datalog_tmp;

    for (int i = 0; i < data_count; i++)
    {
        datalog_tmp = (*head_datalog);
        (*head_datalog) = (*head_datalog)->next;
        free(datalog_tmp->id);
        free(datalog_tmp->pozition);
        free(datalog_tmp);
    }
    *head_datalog = NULL;  // Set the head to NULL after freeing all nodes
}

void id_load(t_data_log **new_datalog_node, char *datastorage){
    (*new_datalog_node)->id->label[0] = datastorage[0];
    (*new_datalog_node)->id->number = atoi(&datastorage[1]);
    (*new_datalog_node)->id->type[0] = datastorage[4];
}

void pozition_load(t_data_log **new_datalog_node, char *datastorage){
    if (datastorage[0] == '-')
        {
            (*new_datalog_node)->pozition->latitude = atof(&datastorage[1])*-1;
            (*new_datalog_node)->pozition->operator_lat[0] = '\0';
        }else
        {
            (*new_datalog_node)->pozition->latitude = atof(&datastorage[0]);
            (*new_datalog_node)->pozition->operator_lat[0] = datastorage[0];
            (*new_datalog_node)->pozition->operator_lat[1] = '\0';
        }
        if (datastorage[8] == '-')
        {
            (*new_datalog_node)->pozition->longitude = atof(&datastorage[9])*-1;
            (*new_datalog_node)->pozition->operator_long[0] = '\0';
        }else
        {
            (*new_datalog_node)->pozition->longitude = atof(&datastorage[8]);
            (*new_datalog_node)->pozition->operator_long[0] = datastorage[0];
            (*new_datalog_node)->pozition->operator_long[1] = '\0';
        }
}

void data_load(char *file_name, t_data_log **head_datalog,int *data_count){
    FILE * fptr = fopen(file_name, "r");
    if (fptr == NULL)
    {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }
    char datastorage[50];
    if ((*head_datalog) != 0)
    {
        free_lists(head_datalog, *data_count);
    }
    while (fscanf(fptr, "%s", datastorage) != -1)
    {
        //new nodes
        t_data_log *new_datalog_node = (t_data_log *)malloc(sizeof(t_data_log));//new node
        new_datalog_node->id = (t_id_list *)malloc(sizeof(t_id_list));  // Allocate memory for the new node
        new_datalog_node->pozition = (t_pozition_list *)malloc(sizeof(t_pozition_list));// Allocate memory for the new node
        //loading data to nodes
        fscanf(fptr, "%s", datastorage);
        if (datastorage[0] == '$')
        {
            fscanf(fptr, "%s", datastorage);
        }
        //handling id
        id_load(&new_datalog_node, datastorage);
        //handling pozition
        fscanf(fptr, "%s", datastorage);
        pozition_load(&new_datalog_node, datastorage);
        //handling rest of data
        fscanf(fptr, "%s", new_datalog_node->unit);
        fscanf(fptr, "%lf", &new_datalog_node->value);
        fscanf(fptr, "%d", &new_datalog_node->time);
        fscanf(fptr, "%d", &new_datalog_node->date);
        new_datalog_node->next = NULL;
        if ((*head_datalog) == NULL)
        {
            (*head_datalog) = new_datalog_node;
        }else
        {
            t_data_log *datalog_ptr = (*head_datalog);
            while (datalog_ptr->next != NULL)
            {
                datalog_ptr = datalog_ptr->next;
            }
            datalog_ptr->next = new_datalog_node;
        }
        (*data_count)++;
    }
    printf("Nacitalo sa %d zaznamov\n", *data_count);

}

void data_output(t_data_log *head_datalog ,int data_count){
    if (data_count == 0)
    {
        return;
    }else
    {
        t_data_log *datalog_ptr = head_datalog;
        int i;
        for (i = 0; i < data_count; i++)
        {
            printf("%d:\n", i+1);
            printf("ID: %c%d%c\t%s\t%.2lf\n", datalog_ptr->id->label[0], datalog_ptr->id->number, datalog_ptr->id->type[0], datalog_ptr->unit, datalog_ptr->value);
            printf("Poz: %s%.4lf\t%s%.4lf\n", head_datalog->pozition->operator_lat,datalog_ptr->pozition->latitude, head_datalog->pozition->operator_long,datalog_ptr->pozition->longitude);
            printf("DaC: %d\t%d\n", datalog_ptr->date, datalog_ptr->time);
            datalog_ptr = datalog_ptr->next;
        }
    }
}

void add_log(t_data_log **head_datalog, int *data_count){
    if ((*head_datalog) == NULL)//if list is empty - data_load function was not called yet
    {
        return;//we can't add node to empty list
    }
    int pozition_in_list;
    scanf("%d", &pozition_in_list);
    t_data_log *new_datalog_node = (t_data_log *)malloc(sizeof(t_data_log));//new node
    new_datalog_node->id = (t_id_list *)malloc(sizeof(t_id_list));  // Allocate memory for the new node
    new_datalog_node->pozition = (t_pozition_list *)malloc(sizeof(t_pozition_list));// Allocate memory for the new node
    char datastorage[50];
    
    //loading data to node
    //handling id
    scanf("%s", datastorage);
    id_load(&new_datalog_node, datastorage);
    //handling pozition
    scanf("%s", datastorage);
    pozition_load(&new_datalog_node, datastorage);
    //handling rest of data
    scanf("%s", new_datalog_node->unit);
    scanf("%lf", &new_datalog_node->value);
    scanf("%d", &new_datalog_node->time);
    scanf("%d", &new_datalog_node->date);
    
    //inserting node to list
    t_data_log *datalog_ptr = (*head_datalog); //temporary pointer to head of list
    if (pozition_in_list > *data_count || pozition_in_list < 1)
    {
        new_datalog_node->next = NULL;
        while (datalog_ptr->next != NULL)
        {
            datalog_ptr = datalog_ptr->next; //shift pointer to the end of list
        }
        datalog_ptr->next = new_datalog_node; //add new node to the end of list
        (*data_count)++;
    }else{
        int i;
        for (i = 0; i < (pozition_in_list-2); i++)//pozition_in_list-2 because we need to transfer order number to index logic and stop one node before the node we want to insert
        {
            datalog_ptr = datalog_ptr->next;
        }
        new_datalog_node->next = datalog_ptr->next;
        datalog_ptr->next = new_datalog_node;
        (*data_count)++;
    }
}

int main(void){
    printf("Zadajte príkaz:\n");
    char command;
    t_data_log *head_datalog = NULL;
    int data_count = 0;
    while (1)
    {
        scanf(" %c", &command);
        switch (command)
        {
        case 'v':
            data_output(head_datalog, data_count);
            break;
        
        case 'n':
            data_load("dataloger_V2.txt", &head_datalog, &data_count);
            break;

        case 'p':
            add_log(&head_datalog, &data_count);
            break;

        case 'z':
            
            break;

        case 'u':
            
            break;
        
        case 'r':
            
            break;
        
        case 'k':
            free_lists(&head_datalog, data_count);
            exit(0);
        default:
            printf("Zadali ste nedefinovaný príkaz, skúste to prosím znovu...\n");
        }
        printf("Zadajte ďalší príkaz...\n");
    }
    return 0;
}