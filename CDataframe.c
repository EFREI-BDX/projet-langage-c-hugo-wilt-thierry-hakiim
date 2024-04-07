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
    int numberOfValues;
    Data valueToInsert;
    int status;
    int type;
    printf("How many values do you want to enter :\n");
    scanf("%d",&numberOfValues);
    printf("Enter the type of value you want to enter (0.int ; 1.char ; 2.float ; 3.double) : \n");
    scanf("%d",&type);
    valueToInsert.type =type;


    for( int i= 0; i<numberOfValues;i++){
        switch (type) {
            case INT_TYPE :
                printf("Enter an integer : ");
                while (scanf("%d", &valueToInsert.value.int_type) != 1) {
                    while (getchar() != '\n');  // Clear the input buffer
                    printf("Invalid input. Please enter an integer: ");
                }
                break;
            case CHAR_TYPE :
                printf("Enter a character : ");
                scanf(" %c",&valueToInsert.value.char_type);
                fflush(stdin);
                break;
            case FLOAT_TYPE :
                printf("Enter a float : ");
                while (scanf("%f", &valueToInsert.value.float_type) != 1) {
                    while (getchar() != '\n');  // Clear the input buffer
                    printf("Invalid input. Please enter a float: ");
                }
                break;
            case DOUBLE_TYPE :
                printf("Enter a double : ");
                while (scanf("%lf", &valueToInsert.value.double_type) != 1) {
                    while (getchar() != '\n');  // Clear the input buffer
                    printf("Invalid input. Please enter an integer: ");
                }
                break;
            default :
                printf("ERROR : unknown type\n");

        }
        status= insert_value(mycol, valueToInsert);
    }
    if (status== -1){
        printf("Error : Failed to insert value.\n");
    }
}