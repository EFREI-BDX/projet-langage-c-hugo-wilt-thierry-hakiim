//
// Created by HugoW on 20/04/2024.
//

#include "linkedList.h"

// Liste chainée
Cell* makeCell(char *title) {
    Cell *newCell = (Cell*)malloc(sizeof(Cell));
    newCell->addressColumn = create_column(title);
    newCell->next = NULL;
    return newCell;
}

Liste inputLinkedList(int size, Liste *myliste) {
    char *title = (char*) malloc((strlen(title) + 1) * sizeof(char));
    for (int i=0; i<size;i++){
        printf("Enter a title : ");
        scanf(" %s", title);
        fillList(title, myliste);
    }
    return (*myliste);
}

void fillList(char* title, Liste* liste) {
    Cell* newCell = makeCell(title);
    int status, type;
    char* endPtr, str;

    printf("Enter number of values :");
    scanf("%s", &str);
    long numberOfVal = strtol(&str, &endPtr, 10);
    for( int j= 0; j<numberOfVal;j++){
        char input[100];
        printf("Enter a value to insert :");
        fflush(stdin);
        fgets(input, 100, stdin);
        type = get_type(input);
        Data val;
        switch (type) {
            case 1:
                val.type = FLOAT_TYPE;
                float resultat_f = atof(input);
                val.value.float_type = resultat_f;
                break;
            case 2:
                val.type = INT_TYPE;
                int resultat_i = atoi(input);
                val.value.int_type = resultat_i;
                break;
            case 3:
                val.type = CHAR_TYPE;
                val.value.char_type = input[0];
                //A changer
                break;
            default:
                val.value.char_type = ' ';
        }
        status = insert_value(newCell->addressColumn, val);
        if (status == 0){
            printf("Error");
        }
    }
    if (*liste == NULL){
        *liste = newCell;
    } else{
        Cell* tempCell = *liste;
        while (tempCell->next !=NULL){
            tempCell = tempCell->next;
        }
        tempCell->next = newCell;
    }
}

void displayList(Liste liste) {
    Cell* temp = liste;
    while(temp->next !=NULL){
        printf("Title : %s Logical size : %d Physical size : %d Data : ", temp->addressColumn->title, temp->addressColumn->LOGICAL_SIZE, temp->addressColumn->PHYSICAL_SIZE);
        display(temp);
        temp = temp->next;
    }
    printf("Title : %s Logical size : %d Physical size : %d Data : ", temp->addressColumn->title, temp->addressColumn->LOGICAL_SIZE, temp->addressColumn->PHYSICAL_SIZE);
    display(temp);
}

void display(const Cell *temp) {
    for (int val = 0; val < temp->addressColumn->LOGICAL_SIZE; val++){
        switch(temp->addressColumn->data[val].type) {
            case INT_TYPE:
                printf("%d ", temp->addressColumn->data[val].value.int_type);
                break;
            case FLOAT_TYPE:
                printf("%.2f ", temp->addressColumn->data[val].value.float_type);
                break;
            case CHAR_TYPE:
                printf("%c ", temp->addressColumn->data[val].value.char_type);
                break;
            default:
                printf("Unknown data type\n");
                break;
        }
    }
    printf("\n");
}

void displayLinkedLinesWithLimit(Liste liste, Data limit){
    Cell* temp = liste;
    while(temp->next !=NULL){
        printf("Title : %s Logical size : %d Physical size : %d Data : ", temp->addressColumn->title, temp->addressColumn->LOGICAL_SIZE, temp->addressColumn->PHYSICAL_SIZE);
        displayLines(&limit, temp);
        temp = temp->next;
    }
    printf("Title : %s Logical size : %d Physical size : %d Data : ", temp->addressColumn->title, temp->addressColumn->LOGICAL_SIZE, temp->addressColumn->PHYSICAL_SIZE);
    displayLines(&limit, temp);
}

void displayLines(Data *limit, const Cell *temp) {
    for (int val = 0; val < temp->addressColumn->LOGICAL_SIZE; val++){
        if (isSameType(&(temp->addressColumn->data[val]), limit)){
            if (compareValues(&(temp->addressColumn->data[val]), limit) == 1){
                switch(temp->addressColumn->data[val].type) {
                    case INT_TYPE:
                        printf("%d ", temp->addressColumn->data[val].value.int_type);
                        break;
                    case FLOAT_TYPE:
                        printf("%.2f ", temp->addressColumn->data[val].value.float_type);
                        break;
                    case CHAR_TYPE:
                        printf("%c ", temp->addressColumn->data[val].value.char_type);
                        break;
                    default:
                        printf("Unknown data type\n");
                        break;
                }
            }
        }
    }
    printf("\n");
}

void displayLinkedColumnsWithLimit(Liste liste, char* title){
    Cell* temp = liste;
    while(temp->next !=NULL){
        printf("Title : %s Logical size : %d Physical size : %d Data : ", temp->addressColumn->title, temp->addressColumn->LOGICAL_SIZE, temp->addressColumn->PHYSICAL_SIZE);
        displayColumns(title, temp);
        temp = temp->next;
    }
    printf("Title : %s Logical size : %d Physical size : %d Data : ", temp->addressColumn->title, temp->addressColumn->LOGICAL_SIZE, temp->addressColumn->PHYSICAL_SIZE);
    displayColumns(title, temp);
}

void displayColumns(char* title, const Cell *temp) {
    for (int val = 0; val < temp->addressColumn->LOGICAL_SIZE; val++){
        if (strcmp(temp->addressColumn->title, title) >0 || strcmp(temp->addressColumn->title, title) ==0){
                switch(temp->addressColumn->data[val].type) {
                    case INT_TYPE:
                        printf("%d ", temp->addressColumn->data[val].value.int_type);
                        break;
                    case FLOAT_TYPE:
                        printf("%.2f ", temp->addressColumn->data[val].value.float_type);
                        break;
                    case CHAR_TYPE:
                        printf("%c ", temp->addressColumn->data[val].value.char_type);
                        break;
                    default:
                        printf("Unknown data type\n");
                        break;
                }
            }
        }

    printf("\n");
}

void addRowToDataFrame(Liste liste) {
    Cell* temp = liste;
    while (temp != NULL) {
        // Input
        int status, type;
        char input[100];

        printf("Enter values for column %s:\n", temp->addressColumn->title);
        printf("Enter value : ");
        fflush(stdin);
        fgets(input, 100, stdin);
        type = get_type(input);
        Data val;
        switch (type) {
            case 1:
                val.type = FLOAT_TYPE;
                val.value.float_type = atof(input);
                break;
            case 2:
                val.type = INT_TYPE;
                val.value.int_type = atoi(input);
                break;
            case 3:
                val.type = CHAR_TYPE;
                val.value.char_type = input[0];
                break;
            default:
                val.value.char_type = ' ';
            }
            status = insert_value(temp->addressColumn, val);
            if (status == 0) {
                printf("Error\n");
            }
        temp = temp->next;
    }
}

void removeRowFromDataFrame(Liste liste, int indexToRemove) {
    Cell* temp = liste;
    while (temp != NULL) {
        printf("Removing values from column %s :\n", temp->addressColumn->title);
        if (temp->addressColumn->LOGICAL_SIZE == 0) {
            printf("Empty \n");
        } else {
            if (indexToRemove>=temp->addressColumn->LOGICAL_SIZE){
                remove_element(temp->addressColumn->data, indexToRemove, temp->addressColumn->LOGICAL_SIZE);
                temp->addressColumn->LOGICAL_SIZE-=1;
                temp->addressColumn->data = (Data*)realloc(temp->addressColumn->data, temp->addressColumn->PHYSICAL_SIZE * sizeof(Data));
            }
        }
        temp = temp->next;
    }
}


void remove_element(Data *data, int index, int array_length)
{
    for(int i = index; i < array_length - 1; i++)
        data[i] = data[i + 1];
}


void removeColumnFromDataFrame(Liste* liste, char* title) {
    if (*liste == NULL) {
        printf("Empty list \n");
        return;
    }
    Cell* temp = *liste;
    Cell* previous = NULL;
    while (temp != NULL && strcmp(temp->addressColumn->title, title) != 0) {
        previous = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Column not found\n");
        return;
    }
    if (previous == NULL) {
        *liste = temp->next;
    } else {
        previous->next = temp->next;
    }
    delete_column(&temp->addressColumn);
    printf("Executed order 66 successfully\n");
}

void renamedColumn(Liste* liste, char* oldTitle, char* newTitle){
    Cell* temp = *liste;
    while (temp != NULL) {
        if (strcmp(temp->addressColumn->title, oldTitle) == 0){
            strcpy(temp->addressColumn->title, newTitle);
        }
        temp = temp->next;
    }
}

int existsInDataframe(Liste liste, Data valToCompare){
    Cell* temp = liste;
    int isFound = 0;
    while (temp != NULL) {
        for (int val = 0; val < temp->addressColumn->LOGICAL_SIZE; val++){
            if (compareValues(&(temp->addressColumn->data[val]), &valToCompare) == 0){
                isFound = 1;
            }
        }
        temp = temp->next;
    }
    return isFound;
}