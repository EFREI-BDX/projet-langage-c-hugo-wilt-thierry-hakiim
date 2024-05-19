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
                    col->data[i]->string_type = (char*)malloc(100 * sizeof(char));
                    scanf("%s", col->data[i]->string_type);
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

void hardFillCDataframe(CDATAFRAME *cdf) {
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

void addColumn(CDATAFRAME *cdf, char *title, ENUM_TYPE type) {
    if (cdf == NULL || title == NULL) return;
    COLUMN *new_col = (COLUMN *)malloc(sizeof(COLUMN));
    new_col->title = strdup(title);
    new_col->LOGICAL_SIZE = 0;
    new_col->PHYSICAL_SIZE = 0;
    new_col->column_type = type;
    new_col->data = NULL;
    new_col->index = NULL;
    LNODE *new_node = (LNODE *)malloc(sizeof(LNODE));
    new_node->data = new_col;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (cdf->tail == NULL) {
        cdf->head = new_node;
        cdf->tail = new_node;
    } else {
        cdf->tail->next = new_node;
        new_node->prev = cdf->tail;
        cdf->tail = new_node;
    }
}

void changeColumnTitle(CDATAFRAME *cdf, char *oldTitle, char *newTitle) {
    if (cdf == NULL || oldTitle == NULL || newTitle == NULL) {
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL) {
        COLUMN* col = current->data;
        if (strcmp(col->title, oldTitle) == 0) {
            free(col->title);
            col->title = strdup(newTitle);
            return;
        }
        current = current->next;
    }
}

int valueExists(CDATAFRAME *cdf, void *value) {
    if (cdf == NULL || value == NULL) return 0;

    LNODE *current = cdf->head;
    while (current != NULL) {
        if (valueExistsInColumn(current->data, value)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
bool valueExistsInColumn(COLUMN *col, void *value) {
    if (col == NULL || value == NULL) return false;

    for (unsigned int i = 0; i < col->LOGICAL_SIZE; i++) {
        switch (col->column_type) {
            case UINT_TYPE:
                if (*(unsigned int*)col->data[i] == *(unsigned int*)value) {
                    return true;
                }
                break;
            case INT_TYPE:
                if (*(int*)col->data[i] == *(int*)value) {
                    return true;
                }
                break;
            case CHAR_TYPE:
                if (*(char*)col->data[i] == *(char*)value) {
                    return true;
                }
                break;
            case FLOAT_TYPE:
                if (*(float*)col->data[i] == *(float*)value) {
                    return true;
                }
                break;
            case DOUBLE_TYPE:
                if (*(double*)col->data[i] == *(double*)value) {
                    return true;
                }
                break;
            case STRING_TYPE:
                if (strcmp((char*)col->data[i], (char*)value) == 0) {
                    return true;
                }
                break;
            case STRUCT_TYPE:
                // Handling for struct types would go here
                break;
            default:
                // Unknown type
                break;
        }
    }
    return false;
}


void* accessCellValue(CDATAFRAME *cdf, unsigned long long rowIndex, unsigned long long colIndex) {
    if (cdf == NULL){
        return NULL;
    }
    LNODE *current = cdf->head;
    unsigned long long colCount = 0;
    while (current != NULL && colCount < colIndex) {
        current = current->next;
        colCount++;
    }
    if (current == NULL){
        return NULL;
    }
    if (rowIndex >= current->data->LOGICAL_SIZE) {
        return NULL;
    }
    return current->data->data[rowIndex];
}

void replaceCellValue(CDATAFRAME *cdf, unsigned int rowIndex, unsigned int colIndex, void *newValue) {
    if (cdf == NULL) return;
    LNODE *current = cdf->head;
    unsigned int colCount = 0;
    while (current != NULL && colCount < colIndex) {
        current = current->next;
        colCount++;
    }
    if (current == NULL) return;
    if (rowIndex >= current->data->LOGICAL_SIZE) return;
    switch (current->data->column_type) {
        case UINT_TYPE:
            *(unsigned int *)current->data->data[rowIndex] = *(unsigned int *)newValue;
            break;
        case INT_TYPE:
            *(int *)current->data->data[rowIndex] = *(int *)newValue;
            break;
        case CHAR_TYPE:
            *(char *)current->data->data[rowIndex] = *(char *)newValue;
            break;
        case FLOAT_TYPE:
            *(float *)current->data->data[rowIndex] = *(float *)newValue;
            break;
        case DOUBLE_TYPE:
            *(double *)current->data->data[rowIndex] = *(double *)newValue;
            break;
        case STRING_TYPE:
            free(current->data->data[rowIndex]->struct_type);
            current->data->data[rowIndex]->string_type = strdup((char *)newValue);
            break;
        case STRUCT_TYPE:
            break;
        default:
            break;
    }
}

void printColumnNames(CDATAFRAME *cdf) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL) {
        printf("%s\n", current->data->title);
        current = current->next;
    }
}

void printNumberOfRows(CDATAFRAME *cdf) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    unsigned int rowCount = current->data->LOGICAL_SIZE;
    printf("Number of rows: %u\n", rowCount);
}

void printNumberOfColumns(CDATAFRAME *cdf) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    unsigned int columnCount = 0;
    while (current != NULL) {
        columnCount++;
        current = current->next;
    }
    printf("Number of columns: %u\n", columnCount);
}


int occurrenceValInDataframe(CDATAFRAME *cdf, void* value) {
    int cpt =0;
    if (cdf == NULL || cdf->head == NULL) {
        return cpt;
    }
    LNODE* current = cdf->head;
    unsigned int columnCount = 0;
    while (current != NULL) {
        cpt += occurrencePart2(current->data, value);
        current = current->next;
    }
    return cpt;
}


int countValuesGreaterThan(CDATAFRAME *cdf, void *value) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return 0;
    }
    int count = 0;
    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = current->data;
        for (unsigned int i = 0; i < col->LOGICAL_SIZE; i++) {
            switch (col->column_type) {
                case UINT_TYPE:
                    if (*(unsigned int *)col->data[i] > *(unsigned int *)value) {
                        count++;
                    }
                    break;
                case INT_TYPE:
                    if (*(int *)col->data[i] > *(int *)value) {
                        count++;
                    }
                    break;
                case CHAR_TYPE:
                    if (*(char *)col->data[i] > *(char *)value) {
                        count++;
                    }
                    break;
                case FLOAT_TYPE:
                    if (*(float *)col->data[i] > *(float *)value) {
                        count++;
                    }
                    break;
                case DOUBLE_TYPE:
                    if (*(double *)col->data[i] > *(double *)value) {
                        count++;
                    }
                    break;
                case STRING_TYPE:
                    if (strcmp((char*)col->data, (char *)value)>0){
                        count++;
                    }
                    break;
                case STRUCT_TYPE:
                    break;
                default:
                    // Unknown type
                    break;
            }
        }
        current = current->next;
    }
    return count;
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

*/