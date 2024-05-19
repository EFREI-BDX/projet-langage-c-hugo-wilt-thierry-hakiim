//
// Created by HugoW on 25/03/2024.
//

#include "columns.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>




/*COLUMN* create_column(char* title){
    COLUMN *newColumn= (COLUMN*) malloc( REALOC_SIZE* sizeof(COLUMN));
    newColumn->title = (char*) malloc((strlen(title) + 1) * sizeof(char));
    strcpy(newColumn->title, title);
    newColumn->PHYSICAL_SIZE = REALOC_SIZE;
    newColumn->LOGICAL_SIZE = 0;
    newColumn->data = (Data*) malloc( REALOC_SIZE* sizeof(Data));
    return newColumn;
}

int insert_value(COLUMN *column, Data value){
    if(column->LOGICAL_SIZE==0 ||column->LOGICAL_SIZE==column->PHYSICAL_SIZE){
        if(column->LOGICAL_SIZE==0){
            column->data=(Data*)malloc((column->LOGICAL_SIZE)+REALOC_SIZE*sizeof(Data));
            column->data[column->LOGICAL_SIZE]=value;
        }else{
            if(column->LOGICAL_SIZE==column->PHYSICAL_SIZE) {
                column->data = realloc(column, (column->PHYSICAL_SIZE + REALOC_SIZE) * sizeof(Data));
                column->data[column->LOGICAL_SIZE] = value;
                column->PHYSICAL_SIZE += REALOC_SIZE;
            }
        }
        column->LOGICAL_SIZE++;
        return 1;
    }else{
        if((column->LOGICAL_SIZE!=0 && column->LOGICAL_SIZE!=column->PHYSICAL_SIZE)){
            column->data[column->LOGICAL_SIZE] = value;
            column->LOGICAL_SIZE++;
            return 1;

        }else{
            return 0;
        }
    }
}

void delete_column(COLUMN **col){
    free((*col)->data);
    free(*col);
}

void print_col(COLUMN* col){
    printf("%s\n", col->title);
    printf("%d\n", col->PHYSICAL_SIZE);
    printf("%d\n", col->LOGICAL_SIZE);
    for (int i =0; i<col->LOGICAL_SIZE;i++){
        switch(col->data[i].value){
            case INT_TYPE :
                printf("%d = %d  ",i, col->data[i].value.int_type);
                break;
            case CHAR_TYPE :
                printf("%d = %c",i,col->data[i].value.char_type);
                break;
            case FLOAT_TYPE :
                printf("%d = %f",i,col->data[i].value.float_type);
                break;
            case DOUBLE_TYPE :
                printf("%d = %lf",i,col->data[i].value.double_type);
                break;
            default :
                printf("ERROR : unknown type.\n");
                break;
        }
        printf("\n");
    }
    printf("\n");
}

int occurrence(COLUMN* col,Data searchValue){
    int cptOccurrence = 0;
    for (int i =0; i<col->LOGICAL_SIZE;i++){
        if (compareValues(&(col->data[i]),&searchValue)==0){
            cptOccurrence +=1;
        }
    }
    return cptOccurrence;
}

Data valueAtIndex(COLUMN* col,int indexValue){
    if (indexValue<col->LOGICAL_SIZE){
        return col->data[indexValue];
    }
    else {
        Data errorData;
        errorData.type = INT_TYPE;
        errorData.value.int_type =-1;
        return errorData;
    }
}

int numberOfValuesAboveSearchValue(COLUMN* col,Data searchValue){
    int cptValuesAboveSearchValue = 0;
    for (int i =0; i<col->LOGICAL_SIZE;i++){
        if (compareValues(&col->data[i], &searchValue)>0){
            cptValuesAboveSearchValue +=1;
        }
    }
    return cptValuesAboveSearchValue;
}

int numberOfValuesUnderSearchValue(COLUMN* col,Data searchValue){
    int cptValuesUnderSearchValue = 0;
    for (int i =0; i<col->LOGICAL_SIZE;i++){
        if (compareValues(&col->data[i], &searchValue)<0){
            cptValuesUnderSearchValue +=1;
        }
    }
    return cptValuesUnderSearchValue;
}

int isSameType(Data* value1, Data* value2){
    return (value1->type == value2->type);
}

int compareValues(Data* value1, Data* value2) {
    if (!isSameType(value1, value2)) {
        printf("Error: The two values are not of the same type.\n");
        return -2;  // Return a special value to indicate an error.
    }
    else {
        switch (value1->type) {
            case INT_TYPE:
                if (value1->value.int_type < value2->value.int_type) return -1;
                if (value1->value.int_type > value2->value.int_type) return 1;
                return 0;
            case CHAR_TYPE:
                if (value1->value.char_type < value2->value.char_type) return -1;
                if (value1->value.char_type > value2->value.char_type) return 1;
                return 0;
            case FLOAT_TYPE:
                if (value1->value.float_type < value2->value.float_type) return -1;
                if (value1->value.float_type > value2->value.float_type) return 1;
                return 0;
            case DOUBLE_TYPE:
                if (value1->value.double_type < value2->value.double_type) return -1;
                if (value1->value.double_type > value2->value.double_type) return 1;
                return 0;
            default:
                printf("Error: Unknown type.\n");
                return -2;
        }
    }
}


int get_type(char* input){
    double x;
    int num;
    char str[20] = "";
    double tolerance = 1e-12;
    if (sscanf(input, "%lf", &x) == 1) {
        num = (int)x; // We cast to int.
        if ( fabs(x - num)/x > tolerance ) {
            //float
            return 1;
        } else {
            //int
            return 2;
        }
    } else if (sscanf(input, "%s", str) == 1) {
        // string
        return 3;
    } else {
        // error
        return -1;
    }
}


int get_type2(char* input){
    if (strcmp(input, "Float") == 0) {
        return 1;
    }
    if (strcmp(input, "Int") == 0) {
        return 2;
    }
    if (strcmp(input, "Char") == 0) {
        return 3;
    }
    if (strcmp(input, "Double") == 0) {
        return 4;
    }
    return 0;
}



void hardFill(COLUMN** array){
    for (int i = 0; i < 3; i++) {
        //title
        char title[10]= "Test";
        title[4] = i;

        array[i] = create_column(title);
        //input
        Data int_test, int_test2, int_test3, char_test, float_test;
        int_test.type = INT_TYPE;
        int_test.value.int_type = 1;
        int_test2.type = INT_TYPE;
        int_test2.value.int_type = 2;
        int_test3.type = INT_TYPE;
        int_test3.value.int_type = 3;
        char_test.type = CHAR_TYPE;
        char_test.value.char_type = 'e';
        float_test.type = FLOAT_TYPE;
        float_test.value.float_type = 3.1;

        insert_value(array[i], int_test);
        insert_value(array[i], float_test);
        insert_value(array[i], int_test2);
        insert_value(array[i], char_test);
        insert_value(array[i], int_test3);

    }
}

*/
COLUMN *createColumnPart2(ENUM_TYPE type, char *title){
    COLUMN *newColumn= (COLUMN*) malloc( REALOC_SIZE* sizeof(COLUMN));
    if (newColumn == NULL) {
        return NULL;
    }
    newColumn->title = strdup(title);
    newColumn->PHYSICAL_SIZE = REALOC_SIZE;
    newColumn->LOGICAL_SIZE = 0;
    newColumn->column_type = type;
    newColumn->index = NULL;
    return newColumn;
}


int insertValuePart2(COLUMN *column, void *value){
    if(column->LOGICAL_SIZE == 0) {
        column->data = (COL_TYPE**)malloc(REALOC_SIZE * sizeof(COL_TYPE*));
        if(column->data == NULL) {
            return 0;
        }
        column->PHYSICAL_SIZE = REALOC_SIZE;
    } else if(column->LOGICAL_SIZE == column->PHYSICAL_SIZE) {
        COL_TYPE **temp = (COL_TYPE**)realloc(column->data, (column->PHYSICAL_SIZE + REALOC_SIZE) * sizeof(COL_TYPE*));
        if(temp == NULL) {
            return 0;
        }
        column->data = temp;
        column->PHYSICAL_SIZE += REALOC_SIZE;
    }

    COL_TYPE *newData= (COL_TYPE *)malloc(sizeof(COL_TYPE));
    if (newData == NULL) {
        return 0;
    }
    if(column->data == NULL) {
        return 0; // column->data has not been allocated memory
    }
    column->data[column->LOGICAL_SIZE]=newData;

    switch(column->column_type){
        case UINT_TYPE:
            column->data[column->LOGICAL_SIZE]->uint_type = *((unsigned int *)value);
            break;
        case INT_TYPE:
            column->data[column->LOGICAL_SIZE]->int_type = *((int *)value);
            break;
        case CHAR_TYPE:
            column->data[column->LOGICAL_SIZE]->char_type = *((char *)value);
            break;
        case FLOAT_TYPE:
            column->data[column->LOGICAL_SIZE]->float_type = *((float *)value);
            break;
        case DOUBLE_TYPE:
            column->data[column->LOGICAL_SIZE]->double_type = *((double *)value);
            break;
        case STRING_TYPE:
            column->data[column->LOGICAL_SIZE]->string_type = strdup((char *)value);
            if (column->data[column->LOGICAL_SIZE]->string_type == NULL) {
                free(column->data[column->LOGICAL_SIZE]);
                column->data[column->LOGICAL_SIZE] = NULL;
                return 0;
            }
            break;
        case STRUCT_TYPE:
            column->data[column->LOGICAL_SIZE]->struct_type = value;
            break;
        default:
            printf("undefined type ");
            free(column->data[column->LOGICAL_SIZE]);
            column->data[column->LOGICAL_SIZE] = NULL;
            return 0;
    }
    column->LOGICAL_SIZE++;
    return 1;
}

void deleteColumnPart2(COLUMN **col){
    free((*col)->title);
    if((*col)->data != NULL){
        if ((*col)->column_type == STRING_TYPE){
            for(int i = 0; i < (*col)->LOGICAL_SIZE; i++){
                free((*col)->data[i]->string_type);
            }
        } else if ((*col)->column_type == STRUCT_TYPE){
            for(int i = 0; i < (*col)->LOGICAL_SIZE; i++){
                free((*col)->data[i]->struct_type);
            }
        } else{
            free((*col)->data);
        }
    }
    free((*col)->index);
    (*col)->index = NULL;
    free(*col);
}
void convertValue(COLUMN *col, unsigned long long int i, char *str, int size){
    if(i>=col->LOGICAL_SIZE){
        printf("index out of range");
        return;
    }
    switch(col->column_type){
        case UINT_TYPE :
            snprintf(str,size,"%u",*((unsigned int*)col->data[i]));
            break;
        case INT_TYPE :
            snprintf(str,size,"%d",*(( int*)col->data[i]));
            break;
        case CHAR_TYPE:
            snprintf(str,size,"%c",*((char*)col->data[i]));
            break;
        case FLOAT_TYPE:
            snprintf(str,size,"%f",*((float*)col->data[i]));
            break;
        case DOUBLE_TYPE :
            snprintf(str,size,"%lf",*((double*)col->data[i]));
            break;
        case STRING_TYPE :
            strncpy(str, (char*)col->data[i], size);
            str[size - 1] = '\0';
            break;
        case STRUCT_TYPE:
            snprintf(str, size, "%p", col->data[i]->struct_type);
            break;
        default:
            printf("Undefined type encountered\n");
            break;
    }
}



int occurrencePart2(COLUMN *col, void *value) {
    if (col == NULL || value == NULL) {
        return 0;
    }
    int cpt = 0;
    for (unsigned long long i = 0; i < col->LOGICAL_SIZE; i++) {
        switch (col->column_type) {
            case UINT_TYPE:
                if (col->data[i]->uint_type == *(unsigned int *)value) {
                    cpt++;
                }
                break;
            case INT_TYPE:
                if (col->data[i]->int_type == *(signed int *)value) {
                    cpt++;
                }
                break;
            case CHAR_TYPE:
                if (col->data[i]->char_type == *(char *)value) {
                    cpt++;
                }
                break;
            case FLOAT_TYPE:
                if (col->data[i]->float_type == *(float *)value) {
                    cpt++;
                }
                break;
            case DOUBLE_TYPE:
                if (col->data[i]->double_type == *(double *)value) {
                    cpt++;
                }
                break;
            case STRING_TYPE:
                if (strcmp(col->data[i]->string_type, (char *)value) == 0) {
                    cpt++;
                }
                break;
            case STRUCT_TYPE:
                // Comparaison des structures non implémentée pour l'instant
                break;
            case NULLVAL:
                break;
            default:
                break;

        }
    }
    return cpt;
}

int numberOfValuesAboveSearchValuePart2(COLUMN *col, void *value) {
    if (col == NULL || value == NULL) {
        return 0;
    }
    int cpt = 0;
    for (unsigned long long i = 0; i < col->LOGICAL_SIZE; i++) {
        switch (col->column_type) {
            case UINT_TYPE:
                if (col->data[i]->uint_type > *(unsigned int *)value) {
                    cpt++;
                }
                break;
            case INT_TYPE:
                if (col->data[i]->int_type > *(signed int *)value) {
                    cpt++;
                }
                break;
            case CHAR_TYPE:
                if (col->data[i]->char_type > *(char *)value) {
                    cpt++;
                }
                break;
            case FLOAT_TYPE:
                if (col->data[i]->float_type > *(float *)value) {
                    cpt++;
                }
                break;
            case DOUBLE_TYPE:
                if (col->data[i]->double_type > *(double *)value) {
                    cpt++;
                }
                break;
            case STRING_TYPE:
                if (strcmp(col->data[i]->string_type, (char *)value) > 0) {
                    cpt++;
                }
                break;
            case STRUCT_TYPE:
                // Comparaison des structures non implémentée pour l'instant
                break;
            case NULLVAL:
                break;
            default:
                break;

        }
    }
    return cpt;
}

int numberOfValuesUnderSearchValuePart2(COLUMN *col, void *value) {
    if (col == NULL || value == NULL) {
        return 0;
    }
    int cpt = 0;
    for (unsigned long long i = 0; i < col->LOGICAL_SIZE; i++) {
        switch (col->column_type) {
            case UINT_TYPE:
                if (col->data[i]->uint_type < *(unsigned int *)value) {
                    cpt++;
                }
                break;
            case INT_TYPE:
                if (col->data[i]->int_type < *(signed int *)value) {
                    cpt++;
                }
                break;
            case CHAR_TYPE:
                if (col->data[i]->char_type < *(char *)value) {
                    cpt++;
                }
                break;
            case FLOAT_TYPE:
                if (col->data[i]->float_type < *(float *)value) {
                    cpt++;
                }
                break;
            case DOUBLE_TYPE:
                if (col->data[i]->double_type < *(double *)value) {
                    cpt++;
                }
                break;
            case STRING_TYPE:
                if (strcmp(col->data[i]->string_type, (char *)value) < 0) {
                    cpt++;
                }
                break;
            case STRUCT_TYPE:
                // Comparaison des structures non implémentée pour l'instant
                break;
            case NULLVAL:
                break;
            default:
                break;
        }
    }
    return cpt;
}

void printValueAtIndex(COLUMN* col, unsigned long long index){
    int size = sizeof(col->column_type);
    char str[5];
    convertValue(col, index, str, size);
    printf("%s", str);
}


void printCol(COLUMN* col){
    if(col==NULL){
        printf("The column is NULL");
        return;
    }
    printf("Title: %s\n",col->title);
    char string[REALOC_SIZE];
    for(unsigned long long int  i=0;i<col->LOGICAL_SIZE;i++){
        printf("[%llu] ", i);
        if(col->data[i]==NULL){
            printf("NULL\n");
        }else{
            convertValue(col,i,string,sizeof(string));
            printf("%s\n",string);
        }
    }
}