//
// Created by HugoW on 20/04/2024.
//

#include "linkedList.h"

// Liste chainée

CDATAFRAME *createCdataframe(ENUM_TYPE *cdftype, int size){
    CDATAFRAME *cdf = (CDATAFRAME *)malloc(sizeof(CDATAFRAME));
    if (cdf==NULL) {
        return NULL;
    }
    cdf->head = NULL;
    cdf->tail = NULL;

    for (int i = 0; i < size; i++) {
        char title[REALOC_SIZE];
        snprintf(title, 20, "Column %d", i+1); // Generate a title for each column
        COLUMN *col = createColumnPart2(cdftype[i], title);

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

void deleteCdataframe(CDATAFRAME** cdf) {
    if (cdf == NULL || *cdf == NULL) return;
    LNODE* current = (*cdf)->head;
    LNODE* next;
    while (current != NULL) {
        deleteColumnPart2(&current->data);
        next = current->next;
        free(current);
        current = next;
    }
    (*cdf)->head = NULL;
    (*cdf)->tail = NULL;
    free(*cdf);
    *cdf = NULL;
}

void deleteColumn(CDATAFRAME *cdf, char *colName) {
    if (cdf == NULL || colName == NULL) return;
    LNODE* current = cdf->head;
    LNODE* prev = NULL;
    while (current != NULL) {
        COLUMN* col = current->data;
        if (strcmp(col->title, colName) == 0) {
            if (prev == NULL) {
                cdf->head = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == cdf->tail) {
                cdf->tail = prev;
            }
            deleteColumnPart2(&col);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int getCdataframeColsCize(CDATAFRAME *cdf) {
    int cpt = 0;
    LNODE* current = cdf->head;
    while (current != NULL) {
        cpt++;
        current = current->next;
    }
    return cpt;
}

void fillCDataframe(CDATAFRAME *cdf) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL) {
        int numberOfValues = 0;
        printf("Number of values for column %s: ", current->data->title);
        scanf("%d", &numberOfValues);
        for (int i = 0; i < numberOfValues; i++) {
            insertValuePart2(current->data, &i);
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

void printCdataframeWithLimit(CDATAFRAME* cdf) {
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

/*Liste *inputLinkedList(int size, Liste *myliste) {
    for (int i=0; i<size;i++){
        char *title = (char*) malloc(MAX_TITLE_NAME_SIZE * sizeof(char));
        printf("Enter a title : ");
        scanf("%s", title);
        fillList(title, myliste);
    }
    return myliste;
}

void fillListPart2(){

}

void fillList(char* title, Liste* liste) {
    CDATAFRAME* newCell = makeCell(title);
    int status, type, typeOfInput, numberOfValues;
    printf("Enter number of values :");
    scanf("%d", &numberOfValues);
    char inputType[20];
    printf("Enter type : ");
    scanf("%s", inputType);
    typeOfInput = get_type2(inputType);
    for( int j= 0; j<numberOfValues;j++){
        char input[100];
        do {
            printf("Enter a value to insert :");
            fflush(stdin);
            fgets(input, 100, stdin);
            type = get_type(input);
        } while( type!= typeOfInput);
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


void removeColumnFromDataFrame(Liste* liste, char* titleToRemove) {
    if (*liste == NULL) {
        printf("Empty list \n");
        return;
    }
    Cell* temp = *liste;
    Cell* previous = NULL;
    while (temp != NULL && strcmp(temp->addressColumn->title, titleToRemove) != 0) {
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

void renameColumn(Liste* liste, char* oldTitle, char* newTitle){
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
        char title[20] = "Test-";
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

*