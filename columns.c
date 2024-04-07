//
// Created by HugoW on 25/03/2024.
//

#include "columns.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


COLUMN *create_column(char* title){
    COLUMN *newColumn= (COLUMN*) malloc( REALOC_SIZE* sizeof(COLUMN));
    newColumn->title = (char*) malloc((strlen(title) + 1) * sizeof(char));
    strcpy(newColumn->title, title);
    newColumn->PHYSICAL_SIZE = REALOC_SIZE;
    newColumn->LOGICAL_SIZE = 0;
    newColumn->data = (Data*) malloc( REALOC_SIZE* sizeof(Data));
    return newColumn;
}

int insert_value(COLUMN *column, Data value){
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
        switch(col->data[i].type){
            case INT_TYPE :
                printf("%d = %d  ",i, col->data[i].value.int_type);
                break;
            case CHAR_TYPE :
                printf("%d = %c",i,col->data[i].value.char_type);
                break;
            case FLOAT_TYPE :
                printf("%d = %f",i,col->data[i].value.float_type);
                break;
            case DOUBLE_TYPE :
                printf("%d = %lf",i,col->data[i].value.double_type);
                break;
            default :
                printf("ERROR : unknown type.\n");
                break;
        }
        printf("\n");
    }
    printf("\n");
}

int occurrence(COLUMN* col,Data searchValue){
    int cptOccurrence = 0;
    for (int i =0; i<col->LOGICAL_SIZE;i++){
        if (compareValues(&(col->data[i]),&searchValue)==0){
            cptOccurrence +=1;
        }
    }
    return cptOccurrence;
}

Data valueAtIndex(COLUMN* col,int indexValue){
    if (indexValue<col->LOGICAL_SIZE){
        return col->data[indexValue];
    }
    else {
        Data errorData;
        errorData.type = INT_TYPE;
        errorData.value.int_type =-1;
        return errorData;
    }
}

int numberOfValuesAboveSearchValue(COLUMN* col,Data searchValue){
    int cptValuesAboveSearchValue = 0;
    for (int i =0; i<col->LOGICAL_SIZE;i++){
        if (compareValues(&col->data[i], &searchValue)>0){
            cptValuesAboveSearchValue +=1;
        }
    }
    return cptValuesAboveSearchValue;
}

int numberOfValuesUnderSearchValue(COLUMN* col,Data searchValue){
    int cptValuesUnderSearchValue = 0;
    for (int i =0; i<col->LOGICAL_SIZE;i++){
        if (compareValues(&col->data[i], &searchValue)<0){
            cptValuesUnderSearchValue +=1;
        }
    }
    return cptValuesUnderSearchValue;
}

int isSameType(Data* value1, Data* value2){
    return (value1->type == value2->type);
}

int compareValues(Data* value1, Data* value2) {
    if (!isSameType(value1, value2)) {
        printf("Error: The two values are not of the same type.\n");
        return -2;  // Return a special value to indicate an error.
    }
    else {
        switch (value1->type) {
            case INT_TYPE:
                if (value1->value.int_type < value2->value.int_type) return -1;
                if (value1->value.int_type > value2->value.int_type) return 1;
                return 0;
            case CHAR_TYPE:
                if (value1->value.char_type < value2->value.char_type) return -1;
                if (value1->value.char_type > value2->value.char_type) return 1;
                return 0;
            case FLOAT_TYPE:
                if (value1->value.float_type < value2->value.float_type) return -1;
                if (value1->value.float_type > value2->value.float_type) return 1;
                return 0;
            case DOUBLE_TYPE:
                if (value1->value.double_type < value2->value.double_type) return -1;
                if (value1->value.double_type > value2->value.double_type) return 1;
                return 0;
            default:
                printf("Error: Unknown type.\n");
                return -2;
        }
    }
}

tableau createEmptyCDataframe(){
    tableau emptyDataFrame = (COLUMN*) malloc(REALOC_SIZE*sizeof(COLUMN));
    return emptyDataFrame;
}


tableau* inputFillCDataframe(tableau *DataFrame){
    /// Dataframe??
    char *title = (char*) malloc((strlen(title) + 1) * sizeof(char));
    printf("Enter a title : ");
    scanf("%s", title);
    int numberOfValues, status;
    char valueToInsert;
    printf("Enter number of values : ");
    scanf("%d", &numberOfValues);
    for( int i= 0; i<numberOfValues;i++){
        printf("Enter a value to insert : ");
        fgets(&valueToInsert, 256, stdin);
        Data val;

        //status = insert_value(*DataFrame, valueToInsert);

    }
    return DataFrame;
}

int get_type(){
    char input[100] = "";
    double x;
    int num;
    char str[20] = "";
    int assignment[5] = {0};
    double tolerance = 1e-12;

    printf("Pls. provide input: ");
    fgets(input, 100, stdin);

    if (sscanf(input, "%lf", &x) == 1) {
        // Is it a number? All integers are also doubles.
        num = (int)x; // We cast to int.
        if ( fabs(x - num)/x > tolerance ) {
            //float
            return 1;
        } else {
            //int
            return 2;
        }
    } else if (sscanf(input, "%s", str) == 1) {
        // string
        return 3;
    } else {
        // error
        return -1;
    }
}