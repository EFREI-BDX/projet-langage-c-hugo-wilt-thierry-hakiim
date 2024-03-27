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
        if((column->LOGICAL_SIZE!=0 && column->LOGICAL_SIZE!=column->PHYSICAL_SIZE)){
            column->data[column->LOGICAL_SIZE] = value;
            column->LOGICAL_SIZE++;
            return 1;

        }else{
            return 0;
        }
    }
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
    printf("\n");
}

int occurrence(COLUMN* col,Data searchValue){
    int cptOccurrence = 0;
    for (int i =0; i<col->LOGICAL_SIZE;i++){
        if (col->data[i] == searchValue){
            // Faire fonction pour comparer valeurs (chaine de c
            cptOccurrence +=1;
        }
    }
    return cptOccurrence;
}

int valueAtIndex(COLUMN* col,int indexValue){
    if (indexValue<col->LOGICAL_SIZE){
        return col->data[indexValue];
    }
    else return -1;
}

int numberOfValuesAboveSearchValue(COLUMN* col,Data searchValue){
    int cptValuesAboveSearchValue = 0;
    for (int i =0; i<col->LOGICAL_SIZE;i++){
        if (col->data[i] < searchValue){
            cptValuesAboveSearchValue +=1;
        }
    }
    return cptValuesAboveSearchValue;
}

int numberOfValuesUnderSearchValue(COLUMN* col,Data searchValue){
    int cptValuesUnderSearchValue = 0;
    for (int i =0; i<col->LOGICAL_SIZE;i++){
        if (col->data[i] > searchValue){
            cptValuesUnderSearchValue +=1;
        }
    }
    return cptValuesUnderSearchValue;
}

