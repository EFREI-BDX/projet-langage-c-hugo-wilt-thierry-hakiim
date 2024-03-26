//
// Created by Administrateur on 25/03/2024.
//

#ifndef PROJET_LANGAGE_C_COLUMN_H
#define PROJET_LANGAGE_C_COLUMN_H
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
int insert_value(COLUMN *column, int value);



#endif //PROJET_LANGAGE_C_COLUMNS_H

#endif //PROJET_LANGAGE_C_COLUMN_H
