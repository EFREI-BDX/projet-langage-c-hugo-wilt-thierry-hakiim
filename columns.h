//
// Created by HugoW on 25/03/2024.
//

#ifndef PROJET_LANGAGE_C_COLUMNS_H
#define PROJET_LANGAGE_C_COLUMNS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REALOC_SIZE 256
enum enum_type{
    NULLVAL=1,
    UINT_TYPE,
    INT_TYPE,
    CHAR_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    STRUCT_TYPE,
};
typedef enum enum_type ENUM_TYPE;

union column_type{
    unsigned int uint_type;
    signed int int_type;
    char char_type;
    float float_type;
    double double_type;
    char* string_type;
    void* struct_type;
};
typedef union column_type COL_TYPE;

struct column {
    char *title;
    unsigned int LOGICAL_SIZE;
    unsigned int PHYSICAL_SIZE;
    ENUM_TYPE column_type;
    COL_TYPE **data;
    unsigned long long int *index;
    int valid_index;
    unsigned index_size;
    int sort_dir;
};

typedef struct column COLUMN;

COLUMN *createcolumnPart2(ENUM_TYPE type, char *title);
int insertvaluePart2(COLUMN *column, void *type);
void deletecolumnPart2(COLUMN **col);
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);
int occurrencePart2(COLUMN *col, void *value);
int numberOfValuesAboveSearchValuePart2(COLUMN *col, void *value);
int numberOfValuesUnderSearchValuePart2(COLUMN *col, void *value);
void printValueAtIndex(COLUMN* col, unsigned long long index);
void printCol(COLUMN* col);


#endif //PROJET_LANGAGE_C_COLUMNS_H
