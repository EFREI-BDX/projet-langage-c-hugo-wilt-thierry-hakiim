//
// Created by HugoW on 25/03/2024.
//

#ifndef PROJET_LANGAGE_C_COLUMNS_H
#define PROJET_LANGAGE_C_COLUMNS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REALOC_SIZE 256

typedef int Data;

typedef struct {
    char* title;
    int PHYSICAL_SIZE;
    int LOGICAL_SIZE;
    Data* data;
} COLUMN;


COLUMN *create_column(char* title);
void insertValue(COLUMN *column, int value);

void delete_column(COLUMN **col);
void print_col(COLUMN* col);


#endif //PROJET_LANGAGE_C_COLUMNS_H
