#include <stdio.h>
#include "columns.h"
#include "linkedList.h"
#include "sort.h"

int main(){
    int partSelection, functionSelection, typeOfColumn, numberOfValues;
    char title[20];
    printf("Please enter which part of the project you want to test. \nFor columns : 1 \nFor Dataframe : 2 \nSort : 3\nElse : 4\n");
    scanf("%d", &partSelection);
    if (partSelection == 1){
        ENUM_TYPE cdftype [] = {UINT_TYPE,INT_TYPE,CHAR_TYPE,FLOAT_TYPE,DOUBLE_TYPE,STRING_TYPE};
        printf("Enter value for type : \n1 for UINT\n2 for INT\n3 for char\n4 for float\n5 for double\n6 for string\n");
        scanf("%d", &typeOfColumn);
        printf("Enter a title\n");
        scanf("%s", title);
        COLUMN *mycol = createColumnPart2(cdftype[typeOfColumn-1], title);
        printf("Choose function\n1 to create column with type\n2 for stats\n");
        scanf("%d", &functionSelection);
        if (functionSelection == 1){
            printf("Choose number of values :\n");
            scanf("%d", &numberOfValues);
            if (typeOfColumn == 4 || typeOfColumn == 5){
                double number = 353.232;
                for (int i =1; i<=numberOfValues;i++){
                    insertValuePart2(mycol, &number);
                    number+=i*10;
                }
            } else if (typeOfColumn ==6){
                insertValuePart2(mycol, "Lima");
                insertValuePart2(mycol, "Bravo");
                insertValuePart2(mycol, "Zulu");
                insertValuePart2(mycol, "Tango");
            } else{
                for (int i =1; i<=numberOfValues;i++){
                    insertValuePart2(mycol, &i);
                }
            }
            printCol(mycol);
        } else if (functionSelection == 2){
            int typeOfVal;
            if (typeOfColumn == 6){
                insertValuePart2(mycol, "Lima");
                insertValuePart2(mycol, "Bravo");
                insertValuePart2(mycol, "Zulu");
                insertValuePart2(mycol, "Tango");
            } else{
                for (int i =1; i<=5;i++){
                    insertValuePart2(mycol, &i);
                }
            }
            ENUM_TYPE cdftype [] = {UINT_TYPE,INT_TYPE,CHAR_TYPE,FLOAT_TYPE,DOUBLE_TYPE,STRING_TYPE};
            printf("Enter value of type to search : \n1 for UINT\n2 for INT\n3 for char\n4 for float\n5 for double\n6 for string\n");
            scanf("%d", &typeOfVal);
            if (typeOfColumn == typeOfVal){
                unsigned int valueUINT;
                int valueINT;
                char valueCHAR;
                float valueFLOAT;
                double valueDOUBLE;
                char* valueSTRING = malloc(20*sizeof (char));
                printf("Enter value  : ");
                fflush(stdin);
                switch (typeOfVal){
                    case 1:
                        scanf("%u", &valueUINT);
                        printCol(mycol);
                        printf("%d : occurrences of %u\n", occurrencePart2(mycol, &valueUINT), valueUINT);
                        printf("%d : number of values above %u\n", numberOfValuesAboveSearchValuePart2(mycol, &valueUINT), valueUINT);
                        printf("%d : number of values under %u\n", numberOfValuesUnderSearchValuePart2(mycol, &valueUINT), valueUINT);
                        break;
                    case 2:
                        scanf("%d", &valueINT);
                        printCol(mycol);
                        printf("%d : occurrences of %d\n", occurrencePart2(mycol, &valueINT), valueINT);
                        printf("%d : number of values above %d\n", numberOfValuesAboveSearchValuePart2(mycol, &valueINT), valueINT);
                        printf("%d : number of values under %d\n", numberOfValuesUnderSearchValuePart2(mycol, &valueINT), valueINT);
                        break;
                    case 3:
                        scanf(" %c", &valueCHAR);
                        printCol(mycol);
                        printf("%d : occurrences of %c\n", occurrencePart2(mycol, &valueCHAR), valueCHAR);
                        printf("%d : number of values above %c\n", numberOfValuesAboveSearchValuePart2(mycol, &valueCHAR), valueCHAR);
                        printf("%d : number of values under %c\n", numberOfValuesUnderSearchValuePart2(mycol, &valueCHAR), valueCHAR);
                        break;
                    case 4:
                        scanf("%f", &valueFLOAT);
                        printCol(mycol);
                        printf("%d : occurrences of %f\n", occurrencePart2(mycol, &valueFLOAT), valueFLOAT);
                        printf("%d : number of values above %f\n", numberOfValuesAboveSearchValuePart2(mycol, &valueFLOAT), valueFLOAT);
                        printf("%d : number of values under %f\n", numberOfValuesUnderSearchValuePart2(mycol, &valueFLOAT), valueFLOAT);
                        break;
                    case 5:
                        scanf("%lf", &valueDOUBLE);
                        printCol(mycol);
                        printf("%d  : occurrences of %lf\n", occurrencePart2(mycol, &valueDOUBLE), valueDOUBLE);
                        printf("%d : number of values above %lf\n", numberOfValuesAboveSearchValuePart2(mycol, &valueDOUBLE), valueDOUBLE);
                        printf("%d : number of values under %lf\n", numberOfValuesUnderSearchValuePart2(mycol, &valueDOUBLE), valueDOUBLE);
                        break;
                    case 6:
                        scanf("%s", valueSTRING);
                        printCol(mycol);
                        printf("%d  : occurrences of %s\n", occurrencePart2(mycol, valueSTRING), valueSTRING);
                        printf("%d : number of values above %s\n", numberOfValuesAboveSearchValuePart2(mycol, valueSTRING), valueSTRING);
                        printf("%d : number of values under %s\n", numberOfValuesUnderSearchValuePart2(mycol, valueSTRING), valueSTRING);
                        break;
                    default:
                        printf("Error 418 : I'm a teapot!\n");
                }
            } else{
                printf("Not same type :c \n");
            }
        }
    } else if (partSelection ==2){
        ENUM_TYPE cdftype [] = {UINT_TYPE,CHAR_TYPE,STRING_TYPE};
        CDATAFRAME *cdf = createCdataframe(cdftype, 3);
        int searchValue = 10;
        int count = countValuesLesserThan(cdf, &searchValue);
        //printf("Number of values greater than %d: %d\n", searchValue, count);
        printf("Choose function : \n1 for size of dataframe\n2 for fill\n3 for print with limit\n4 for search\n5 to add col\n6 replace val at index\n7 change title\n");
        scanf("%d", &functionSelection);
        if (functionSelection == 1){
            printNumberOfColumns(cdf);
            printNumberOfRows(cdf);
        } else if (functionSelection == 2) {
            int typeOfFill;
            printf("1 for hard fill and 2 for input fill\n");
            scanf("%d", &typeOfFill);
            if (typeOfFill==1){
                hardFillCDataframe(cdf);
                printCdataframe(cdf);
            } else if (typeOfFill==2 ){
                fillCDataframe(cdf);
                printCdataframe(cdf);
            }
        } else if (functionSelection == 3){
            int index;
            printf("Enter index\n");
            scanf("%d", &index);
            printCdataframeWithLimit(cdf, index);

        } else if (functionSelection == 4){
            hardFillCDataframe(cdf);
            int typeOfVal;
            printf("Enter value of type to search : \n1 for UINT\n2 for INT\n3 for char\n4 for float\n5 for double\n6 for string\n");
            scanf("%d", &typeOfVal);
            unsigned int valueUINT;
            int valueINT;
            char valueCHAR;
            float valueFLOAT;
            double valueDOUBLE;
            char* valueSTRING = malloc(20*sizeof (char));
            printCdataframe(cdf);
            printf("Enter value  : ");
            fflush(stdin);
            switch (typeOfVal){
                case 1:
                    scanf("%u", &valueUINT);
                    printf("1 if exists in CDataframe 0 otherwise : %d\n", valueExists(cdf, &valueUINT));
                    printf("Number of values greater than val : %d\n", countValuesGreaterThan(cdf, &valueUINT));
                    printf("Number of values lesser than val : %d\n", countValuesLesserThan(cdf, &valueUINT));
                    break;
                case 2:
                    scanf("%d", &valueINT);
                    printf("1 if exists in CDataframe 0 otherwise : %d\n", valueExists(cdf, &valueINT));
                    printf("Number of values greater than val : %d\n", countValuesGreaterThan(cdf, &valueINT));
                    printf("Number of values lesser than val : %d\n", countValuesLesserThan(cdf, &valueINT));
                    break;
                case 3:
                    scanf(" %c", &valueCHAR);
                    printf("1 if exists in CDataframe 0 otherwise : %d\n", valueExists(cdf, &valueCHAR));
                    printf("Number of values greater than val : %d\n", countValuesGreaterThan(cdf, &valueCHAR));
                    printf("Number of values lesser than val : %d\n", countValuesLesserThan(cdf, &valueCHAR));
                    break;
                case 4:
                    scanf("%f", &valueFLOAT);
                    printf("1 if exists in CDataframe 0 otherwise : %d\n", valueExists(cdf, &valueFLOAT));
                    printf("Number of values greater than val : %d\n", countValuesGreaterThan(cdf, &valueFLOAT));
                    printf("Number of values lesser than val : %d\n", countValuesLesserThan(cdf, &valueFLOAT));
                    break;
                case 5:
                    scanf("%lf", &valueDOUBLE);
                    printf("1 if exists in CDataframe 0 otherwise : %d\n", valueExists(cdf, &valueDOUBLE));
                    printf("Number of values greater than val : %d\n", countValuesGreaterThan(cdf, &valueDOUBLE));
                    printf("Number of values lesser than val : %d\n", countValuesLesserThan(cdf, &valueDOUBLE));
                    break;
                case 6:
                    scanf("%s", valueSTRING);
                    printf("1 if exists in CDataframe 0 otherwise : %d\n", valueExists(cdf, valueSTRING));
                    printf("Number of values greater than val : %d\n", countValuesGreaterThan(cdf, valueSTRING));
                    printf("Number of values lesser than val : %d\n", countValuesLesserThan(cdf, valueSTRING));
                    break;
                default:
                    printf("Error 418 : I'm a teapot!\n");
                }
            }

        else if (functionSelection == 5){
            hardFillCDataframe(cdf);
            addColumn(cdf, "New col", CHAR_TYPE);
            printCdataframe(cdf);
        }
        else if (functionSelection == 6){
            hardFillCDataframe(cdf);
            long long int indexRow, indexCol;
            printf("Enter index of row\n");
            scanf("%lld", &indexRow);
            printf("Enter index of col\n");
            scanf("%lld", &indexCol);
            int a = 100;
            replaceCellValue(cdf, indexRow, indexCol, &a);
            printCdataframe(cdf);
        } else if (functionSelection == 7){
            hardFillCDataframe(cdf);
            changeColumnTitle(cdf,"Column 2", "Modified title");
            printCdataframe(cdf);
        }
    }
    else if (partSelection ==3){
        COLUMN *mycol = createColumnPart2(STRING_TYPE, "sorted column");
        insertValuePart2(mycol, "Lima");
        insertValuePart2(mycol, "Bravo");
        insertValuePart2(mycol, "Zulu");
        insertValuePart2(mycol, "Tango");
        printf("Column content before sorting : \n");
        printCol(mycol);
        sort(mycol,ASC);
        printf("Column content after sorting : \n");
        displayColByIndex(mycol);
        int typeOfVal;
        printf("Enter value of type to search : \n1 for UINT\n2 for INT\n3 for char\n4 for float\n5 for double\n6 for string\n");
        scanf("%d", &typeOfVal);
        ENUM_TYPE cdftype [] = {UINT_TYPE,INT_TYPE,CHAR_TYPE,FLOAT_TYPE,DOUBLE_TYPE,STRING_TYPE};
        COLUMN *mycol2 = createColumnPart2(cdftype[typeOfVal-1], "sorted column");
        unsigned int valueUINT;
        int valueINT;
        char valueCHAR;
        float valueFLOAT;
        double valueDOUBLE;
        char* valueSTRING = malloc(20*sizeof (char));
        printf("Enter value : \n");
        int a = 1, b=2,c=3, d=5;
        double e = 3.14, f = 2.71, g = 666.999, h = 123.456;
        fflush(stdin);
        switch (typeOfVal){
            case 1:
                insertValuePart2(mycol2, &a);
                insertValuePart2(mycol2, &b);
                insertValuePart2(mycol2, &c);
                insertValuePart2(mycol2, &d);
                sort(mycol2, ASC);
                displayColByIndex(mycol2);
                scanf("%u", &valueUINT);
                printf("-1: column not sorted, 0: value not found 1: value found, result : %d", searchValueInColumn(mycol2, &valueUINT));
                break;
            case 2:
                insertValuePart2(mycol2, &a);
                insertValuePart2(mycol2, &b);
                insertValuePart2(mycol2, &c);
                insertValuePart2(mycol2, &d);
                sort(mycol2, ASC);
                displayColByIndex(mycol2);
                scanf("%d", &valueINT);
                printf("-1: column not sorted, 0: value not found 1: value found, result : %d", searchValueInColumn(mycol2, &valueUINT));
                break;
            case 3:
                insertValuePart2(mycol2, "a");
                insertValuePart2(mycol2, "b");
                insertValuePart2(mycol2, "c");
                insertValuePart2(mycol2, "d");
                sort(mycol2, ASC);
                displayColByIndex(mycol2);
                scanf(" %c", &valueCHAR);
                printf("-1: column not sorted, 0: value not found 1: value found, result : %d", searchValueInColumn(mycol2, &valueCHAR));
                break;
            case 4:
                insertValuePart2(mycol2, &e);
                insertValuePart2(mycol2, &f);
                insertValuePart2(mycol2, &g);
                insertValuePart2(mycol2, &h);
                sort(mycol2, ASC);
                displayColByIndex(mycol2);
                scanf("%f", &valueFLOAT);
                printf("-1: column not sorted, 0: value not found 1: value found, result : %d", searchValueInColumn(mycol2, &valueFLOAT));
                break;
            case 5:
                insertValuePart2(mycol2, &e);
                insertValuePart2(mycol2, &f);
                insertValuePart2(mycol2, &g);
                insertValuePart2(mycol2, &h);
                sort(mycol2, ASC);
                displayColByIndex(mycol2);
                scanf("%lf", &valueDOUBLE);
                printf("-1: column not sorted, 0: value not found 1: value found, result : %d", searchValueInColumn(mycol2, &valueDOUBLE));
                break;
            case 6:
                insertValuePart2(mycol2, "Lima");
                insertValuePart2(mycol2, "Bravo");
                insertValuePart2(mycol2, "Zulu");
                insertValuePart2(mycol2, "Tango");
                sort(mycol2, ASC);
                displayColByIndex(mycol2);
                scanf("%s", valueSTRING);
                printf("-1: column not sorted, 0: value not found 1: value found, result : %d", searchValueInColumn(mycol2, valueSTRING));
                break;
            default:
                printf("Error 418 : I'm a teapot!\n");
        }
    } if (partSelection == 4){
        printf("Nothing here but take a cookie\n");
    }

    /*

    printf("%d", check_index(mycol));
    eraseIndex(mycol);
    updateIndex(mycol);
    printf("%d", check_index(mycol));*/
    return 0;
}

