//
// Created by HugoW on 25/03/2024.
//

#include "CDataframe.h"
#include "columns.h"
tableau *createEmptyCDataframe(){
    tableau *emptyDataFrame = (tableau *) malloc(sizeof (tableau));
    return emptyDataFrame;
}

int* inputFillCDataframe(tableau *DataFrame){
    char *title = (char*) malloc((strlen(title) + 1) * sizeof(char));
    COLUMN *mycol = create_column(title);
    int numberOfValues, valueToInsert, status;
    scanf("%d", &numberOfValues);
    for( int i= 0; i<numberOfValues;i++){
        printf("Enter a value to insert");
        scanf("%d", &valueToInsert);
        status= insert_value(mycol, valueToInsert);
    }
}