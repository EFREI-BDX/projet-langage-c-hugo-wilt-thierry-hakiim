//
// Created by Administrateur on 25/03/2024.
//

#include "column.h"



COLUMN *create_column(char* title){
    COLUMN *newColumn= (COLUMN*) malloc( REALOC_SIZE* sizeof(COLUMN));;
    strcpy(newColumn->title, title);
    newColumn->PHYSICAL_SIZE = REALOC_SIZE;
    newColumn->LOGICAL_SIZE = 0;
    newColumn->data = (Data*) malloc( REALOC_SIZE* sizeof(Data));
    return newColumn;
}
int insert_value(COLUMN *column, int value){
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
        if(!(column->LOGICAL_SIZE==0 ||column->LOGICAL_SIZE==column->PHYSICAL_SIZE)){
            column->data[column->LOGICAL_SIZE] = value;
            return 1;
        }else{
            return 0;
        }
    }
}
