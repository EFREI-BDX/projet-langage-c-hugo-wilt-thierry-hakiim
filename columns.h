//
// Created by HugoW on 25/03/2024.
//

#ifndef PROJET_LANGAGE_C_COLUMNS_H
#define PROJET_LANGAGE_C_COLUMNS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REALOC_SIZE 256

typedef enum {
    UINT_TYPE,
    INT_TYPE,
    CHAR_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    STRUCT_TYPE,
}DataType;
typedef struct {
    DataType type;
    union {
        unsigned int uint_type;
        signed int int_type;
        char char_type;
        float float_type;
        double double_type;
        char* string_type;
        void* struct_type;
    }value;
}Data;


typedef struct {
    char* title;
    int PHYSICAL_SIZE;
    int LOGICAL_SIZE;
    Data* data;
    DataType typeOfData;
    unsigned long long int *index;
} COLUMN;

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
int get_type2(char* input);

COLUMN *createcolumnPart2(DataType type, char *title);
int insertvaluePart2(COLUMN *column, void *value);
void deletecolumnPart2(COLUMN **col);
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);
void printcolPart2(COLUMN* col);

#endif //PROJET_LANGAGE_C_COLUMNS_H
