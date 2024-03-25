//
// Created by HugoW on 25/03/2024.
//

#include "columns.h"


COLUMN *create_column(char* title){
    COLUMN *newColumn= (COLUMN*) malloc( REALOC_SIZE* sizeof(COLUMN));;
    newColumn->title = (char*) malloc((strlen(title) + 1) * sizeof(char));
    strcpy(newColumn->title, title);
    newColumn->PHYSICAL_SIZE = REALOC_SIZE;
    newColumn->LOGICAL_SIZE = 0;
    newColumn->data = (Data*) malloc( REALOC_SIZE* sizeof(Data));
    return newColumn;
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
        printf("[%d] = %d  ",i, col->data[i]);
    }

}