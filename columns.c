//
// Created by HugoW on 25/03/2024.
//

#include "columns.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


COLUMN *createColumnPart2(ENUM_TYPE type, char *title) {
    COLUMN *newColumn = (COLUMN *)malloc(sizeof(COLUMN));
    if (newColumn == NULL) {
        return NULL;
    }
    newColumn->title = strdup(title);
    newColumn->PHYSICAL_SIZE = REALOC_SIZE;
    newColumn->LOGICAL_SIZE = 0;
    newColumn->column_type = type;
    newColumn->data = (COL_TYPE **)malloc(REALOC_SIZE * sizeof(COL_TYPE *));
    if (newColumn->data == NULL) {
        free(newColumn->title);
        free(newColumn);
        return NULL;
    }
    newColumn->index = NULL;
    newColumn->valid_index = 0;
    newColumn->index_size = 0;
    newColumn->sort_dir = 0;
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

void printCol(COLUMN* col) {
    if (col == NULL) {
        printf("The column is NULL");
        return;
    }
    printf("Title: %s\n", col->title);
    char string[REALOC_SIZE];
    for (unsigned long long int i = 0; i < col->LOGICAL_SIZE; i++) {
        printf("[%llu] ", i);
        if (col->data[i] == NULL) {
            printf("NULL\n");
        } else {
            switch (col->column_type) {
                case STRING_TYPE:
                    if (col->data[i]->string_type == NULL) {
                        printf("NULL\n");
                    } else {
                        printf("%s\n", col->data[i]->string_type);
                    }
                    break;
                default:
                    convertValue(col, i, string, sizeof(string));
                    printf("%s\n", string);
            }
        }
    }
}