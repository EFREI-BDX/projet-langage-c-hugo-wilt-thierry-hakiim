//
// Created by HugoW on 25/03/2024.
//

#ifndef PROJET_LANGAGE_C_COLUMNS_H
#define PROJET_LANGAGE_C_COLUMNS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REALOC_SIZE 256
#include "CDataframe.h"

typedef enum {
    INT_TYPE,
    CHAR_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
}DataType;
typedef struct {
    DataType type;
    union {
        int int_type;
        char char_type;
        float float_type;
        double double_type;
    }value;
}Data;



typedef struct {
    char* title;
    int PHYSICAL_SIZE;
    int LOGICAL_SIZE;
    Data* data;
} COLUMN;

typedef COLUMN* tableau;

COLUMN* create_column(char* title);
int insert_value(COLUMN* column, Data value);
void delete_column(COLUMN **col);
void print_col(COLUMN* col);
int occurrence(COLUMN* col, Data searchValue);
Data valueAtIndex(COLUMN* col,int indexValue);
int numberOfValuesAboveSearchValue(COLUMN* col,Data searchValue);
int numberOfValuesUnderSearchValue(COLUMN* col,Data searchValue);
int isSameType(Data* value1, Data* value2);
int compareValues(Data* value1, Data* value2);





int get_type(char* input);
COLUMN** createEmptyCDataframe(int size);
void fillArray(COLUMN** array, int size);
void displayColumns(COLUMN** array, int size);
#endif //PROJET_LANGAGE_C_COLUMNS_H
