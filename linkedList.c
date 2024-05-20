//
// Created by HugoW on 20/04/2024.
//

#include "linkedList.h"
#include "columns.h"

/*// Liste chainée
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
            if (indexToRemove<=temp->addressColumn->LOGICAL_SIZE){
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
            if (isSameType(&(temp->addressColumn->data[val]), &valToCompare)){
                if (compareValues(&(temp->addressColumn->data[val]), &valToCompare) == 0){
                    isFound = 1;
                }
            }
        }
        temp = temp->next;
    }
    return isFound;
}

void accessValueAtIndex(Liste liste, int lineNumber, int columnNumber){
    Cell* temp = liste;
    int cpt = 0;
    while (temp != NULL){
        if (cpt == columnNumber){
            if (lineNumber>=temp->addressColumn->LOGICAL_SIZE){
                printf("Value index out of range\n");
            } else {
                switch(temp->addressColumn->data[lineNumber].type) {
                    case INT_TYPE:
                        printf("%d\n", temp->addressColumn->data[lineNumber].value.int_type);
                        break;
                    case FLOAT_TYPE:
                        printf("%.2f\n", temp->addressColumn->data[lineNumber].value.float_type);
                        break;
                    case CHAR_TYPE:
                        printf("%c\n", temp->addressColumn->data[lineNumber].value.char_type);
                        break;
                    default:
                        printf("Unknown data type\n");
                        break;
                }
            }
        }
        cpt+=1;
        temp = temp->next;
    }
}

void replaceValueAtIndex(Liste liste, int lineNumber, int columnNumber){
    Cell* temp = liste;
    int cpt = 0;
    while (temp != NULL){
        if (cpt == columnNumber){
            if (lineNumber>=temp->addressColumn->LOGICAL_SIZE){
                printf("Value index out of range");
            } else {
                char input[20];
                int type;
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
                temp->addressColumn->data[lineNumber] = val;
            }
        }
        cpt+=1;
        temp = temp->next;
    }
}

void displayColumnsNames(Liste liste){
    Cell* temp = liste;
    while (temp!=NULL){
        printf("%s ", temp->addressColumn->title);
        temp = temp->next;
    }
}

int numberOfLines(Liste liste){
    Cell* temp = liste;
    int cpt = 0;
    while (temp!=NULL){
        cpt+= temp->addressColumn->LOGICAL_SIZE;
        temp = temp->next;
    }
    return cpt;
}

int numberOfColumns(Liste liste){
    Cell* temp = liste;
    int cpt = 0;
    while (temp!=NULL){
        cpt+=1;
        temp = temp->next;
    }
    return cpt;
}

int numberOfCellsEqualToVal(Liste liste, Data valToCompare){
    Cell* temp = liste;
    int cpt = 0;
    while (temp!=NULL){
        for (int val = 0; val < temp->addressColumn->LOGICAL_SIZE; val++){
            if (isSameType(&(temp->addressColumn->data[val]), &valToCompare)){
                if (compareValues(&(temp->addressColumn->data[val]), &valToCompare) == 0){
                    cpt += 1;
                }
            }
        }
        temp = temp->next;
    }
    return cpt;
}


int numberOfCellsUnderVal(Liste liste, Data valToCompare){
    Cell* temp = liste;
    int cpt = 0;
    while (temp!=NULL){
        for (int val = 0; val < temp->addressColumn->LOGICAL_SIZE; val++){
            if (isSameType(&(temp->addressColumn->data[val]), &valToCompare)){
                if (compareValues(&(temp->addressColumn->data[val]), &valToCompare) == -1){
                    cpt += 1;
                }
            }
        }
        temp = temp->next;
    }
    return cpt;
}

int numberOfCellsAboveVal(Liste liste, Data valToCompare){
    Cell* temp = liste;
    int cpt = 0;
    while (temp!=NULL){
        for (int val = 0; val < temp->addressColumn->LOGICAL_SIZE; val++){
            if (isSameType(&(temp->addressColumn->data[val]), &valToCompare)){
                if (compareValues(&(temp->addressColumn->data[val]), &valToCompare) == 1){
                    cpt += 1;
                }
            }
        }
        temp = temp->next;
    }
    return cpt;
}

void hardFillLinked(Liste* liste){
    Data int_test1, int_test2, int_test3, char_test1, char_test2, char_test3,float_test1,float_test2,float_test3;
    int_test1.type = INT_TYPE;
    int_test1.value.int_type = 1;
    int_test2.type = INT_TYPE;
    int_test2.value.int_type = 2;
    int_test3.type = INT_TYPE;
    int_test3.value.int_type = 3;
    char_test1.type = CHAR_TYPE;
    char_test1.value.char_type = 'a';
    char_test2.type = CHAR_TYPE;
    char_test2.value.char_type = 'b';
    char_test3.type = CHAR_TYPE;
    char_test3.value.char_type = 'c';
    float_test1.type = FLOAT_TYPE;
    float_test1.value.float_type = 3.14;
    float_test2.type = FLOAT_TYPE;
    float_test2.value.float_type = 2.71;
    float_test3.type = FLOAT_TYPE;
    float_test3.value.float_type = 0.1;
    for (int i=0; i<3;i++){
        char title[20] = "Test ";
        if (i == 0){
            strcat(title, "int");
        }
        if (i == 1){
            strcat(title, "char");
        }
        if (i == 2){
            strcat(title, "float");
        }
        Cell* newCell = makeCell(title);
        if (i==0){
            insert_value(newCell->addressColumn, int_test1);
            insert_value(newCell->addressColumn, int_test2);
            insert_value(newCell->addressColumn, int_test3);
        }
        if (i==1){
            insert_value(newCell->addressColumn, char_test1);
            insert_value(newCell->addressColumn, char_test2);
            insert_value(newCell->addressColumn, char_test3);
        }
        if (i==2){
            insert_value(newCell->addressColumn, float_test1);
            insert_value(newCell->addressColumn, float_test2);
            insert_value(newCell->addressColumn, float_test3);
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

}*/
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size){

    CDATAFRAME *cdf = (CDATAFRAME *)malloc(sizeof(CDATAFRAME));
    if (cdf==NULL) {
        return NULL;
    }
    cdf->head = NULL;
    cdf->tail = NULL;

    for (int i = 0; i < size; i++) {
        char title[REALOC_SIZE];
        snprintf(title, 20, "Column %d", i+1); // Generate a title for each column
        COLUMN *col = createcolumnPart2(cdftype[i], title);

        if(col == NULL){
           return NULL;
       }
        LNODE *node=(LNODE*)malloc(sizeof(LNODE));
        if(node==NULL){
            return NULL;
        }
        node->data=col;
        if (cdf->head == NULL) {
            node->prev = NULL;
            node->next = NULL;
            cdf->head = node;
            cdf->tail = node;
        }else{
            node->prev=cdf->tail;
            node->next=NULL;
            cdf->tail->next = node;
            cdf->tail = node;
        }
    }

    return cdf;

}
void delete_cdataframe(CDATAFRAME** cdf) {
    if (cdf == NULL || *cdf == NULL) return;
    LNODE* current = (*cdf)->head;
    LNODE* next;
    while (current != NULL) {
        deletecolumnPart2(&current->data);
        next = current->next;
        free(current);
        current = next;
    }
    (*cdf)->head = NULL;
    (*cdf)->tail = NULL;
    free(*cdf);
    *cdf = NULL;
}

void delete_column(CDATAFRAME *cdf, char *col_name) {
    if (cdf == NULL || col_name == NULL) return;
    LNODE* current = cdf->head;
    LNODE* prev = NULL;
    while (current != NULL) {
        COLUMN* col = current->data;
        if (strcmp(col->title, col_name) == 0) {
            if (prev == NULL) {
                cdf->head = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == cdf->tail) {
                cdf->tail = prev;
            }
            deletecolumnPart2(&col);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}


int get_cdataframe_cols_size(CDATAFRAME *cdf) {
    int cpt = 0;
    LNODE* current = cdf->head;
    while (current != NULL) {
        cpt++;
        current = current->next;
    }
    return cpt;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"

void fillCDataframe(CDATAFRAME *cdf) {
    if (cdf == NULL || cdf->head == NULL) return;
    LNODE* current = cdf->head;
    while (current != NULL) {
        COLUMN* col = current->data;
        printf("Number of values for column %s: ", col->title);
        int numberOfValues;
        scanf("%d", &numberOfValues);
        col->LOGICAL_SIZE = numberOfValues;
        col->data = (COL_TYPE**)malloc(numberOfValues * sizeof(COL_TYPE*));

        for (int i = 0; i < numberOfValues; i++) {
            col->data[i] = (COL_TYPE*)malloc(sizeof(COL_TYPE));
            printf("Enter value %d for column %s: ", i + 1, col->title);
            switch (col->column_type) {
                case UINT_TYPE:
                    scanf("%u", &col->data[i]->uint_type);
                    break;
                case INT_TYPE:
                    scanf("%d", &col->data[i]->int_type);
                    break;
                case CHAR_TYPE:
                    scanf(" %c", &col->data[i]->char_type);
                    break;
                case FLOAT_TYPE:
                    scanf("%f", &col->data[i]->float_type);
                    break;
                case DOUBLE_TYPE:
                    scanf("%lf", &col->data[i]->double_type);
                    break;
                case STRING_TYPE:
                    col->data[i]->string_type = (char*)malloc(101 * sizeof(char)); // Allocate 101 bytes for the string and the null terminator
                    scanf(" %[^\n]s", col->data[i]->string_type);
                    col->data[i]->string_type[100] = '\0'; // Ensure the string is null-terminated
                    break;
                case STRUCT_TYPE:
                    printf("Struct input not implemented.\n");
                    break;
                case NULLVAL:
                    printf("NULL");
                    break;
                default:
                    printf("Unknown type.\n");
                    break;
            }
        }
        current = current->next;
    }
}

void printCdataframe(CDATAFRAME* cdf) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL) {
        printCol(current->data);
        current = current->next;
    }
}

void printCdataframeWithLimit(CDATAFRAME* cdf, int limitIndex) {
    int cpt =0;
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL && cpt<limitIndex) {
        printCol(current->data);
        current = current->next;
        cpt+=1;
    }
}
void addLineToCdataFrame(CDATAFRAME *cdf, void **values){
    int i=0;
    if(cdf==NULL || values==0){
        return;
    }
    LNODE *current=cdf->head;
    while(current!=NULL){
        COLUMN *col=current->data;
        COL_TYPE* new_value = (COL_TYPE*)malloc(sizeof(COL_TYPE));
        switch (col->column_type) {
            case UINT_TYPE:
                new_value->uint_type = *(unsigned int*)values[i];
                break;
            case INT_TYPE:
                new_value->int_type = *(signed int*)values[i];
                break;
            case CHAR_TYPE:
                new_value->char_type = *(char*)values[i];
                break;
            case FLOAT_TYPE:
                new_value->float_type = *(float*)values[i];
                break;
            case DOUBLE_TYPE:
                new_value->double_type = *(double*)values[i];
                break;
            case STRING_TYPE:
                new_value->string_type = strdup((char*)values[i]);
                break;
            case STRUCT_TYPE:

                break;
            case NULLVAL:

                break;
            default:
                break;
        }
        col->data = (COL_TYPE**)realloc(col->data, (col->LOGICAL_SIZE + 1) * sizeof(COL_TYPE*));
        col->data[col->LOGICAL_SIZE] = new_value;
        col->LOGICAL_SIZE++;

        current = current->next;
        i++;
    }
}
void deleteLineFromCdataFrame(CDATAFRAME *cdf, int lineIndex) {

    if (cdf == NULL) {
        return;
    }
    LNODE *current = cdf->head;
    while(current!=NULL){
        COLUMN *col=current->data;
        if(col->LOGICAL_SIZE > lineIndex){
            for(int i=lineIndex;i<col->LOGICAL_SIZE-1;i++){
                col->data[i]=col->data[i+1];
            }
            col->LOGICAL_SIZE--;
        }
        current=current->next;
    }
}