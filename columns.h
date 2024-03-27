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

typedef int Data;
typedef int searchValue;

typedef struct {
    char* title;
    int PHYSICAL_SIZE;
    int LOGICAL_SIZE;
    Data* data;
} COLUMN;


COLUMN *create_column(char* title);
int insert_value(COLUMN* column, int value);
void delete_column(COLUMN **col);
void print_col(COLUMN* col);
int occurrence(COLUMN* col, Data searchValue);
int valueAtIndex(COLUMN* col,int indexValue);
int numberOfValuesAboveSearchValue(COLUMN* col,Data searchValue);
int numberOfValuesUnderSearchValue(COLUMN* col,Data searchValue);


#endif //PROJET_LANGAGE_C_COLUMNS_H
