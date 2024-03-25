//
// Created by HugoW on 25/03/2024.
//

#include "columns.h"


COLUMN *create_column(char* title){
    COLUMN *newColumn= (COLUMN*) malloc( REALOC_SIZE* sizeof(COLUMN));;
    strcpy(newColumn->title, title);
    newColumn->PHYSICAL_SIZE = REALOC_SIZE;
    newColumn->LOGICAL_SIZE = 0;
    newColumn->data = (Data*) malloc( REALOC_SIZE* sizeof(Data));
    return newColumn;
}