#include <stdio.h>
#include "columns.h"
#include "linkedList.h"


int main() {
    /*
      int size = 3;
      Liste myliste=NULL;
      inputLinkedList(size, &myliste);
      displayList(myliste);
      //displayLinkedLinesWithLimit(myliste, int_test2);
      //displayLinkedColumnsWithLimit(myliste, "Test1");
      //addRowToDataFrame(myliste);
      //removeRowFromDataFrame(myliste, 2);
      //removeColumnFromDataFrame(&myliste, "Test");
      /*renamedColumn(&myliste, "Test", "hello22");
      Data int_test2;
      int_test2.type = INT_TYPE;
      int_test2.value.int_type = 2;
      printf("%d\n",existsInDataframe(myliste, int_test2));
      accessValueAtIndex(myliste, 1, 1);
      replaceValueAtIndex(myliste, 1, 1);
      accessValueAtIndex(myliste, 1, 1);
      displayColumnsNames(myliste);

      //displayList(myliste);
      Data int_test2;
      int_test2.type = INT_TYPE;
      int_test2.value.int_type = 2;
      printf("%d\n", numberOfColumns(myliste));
      printf("%d\n", numberOfLines(myliste));
      printf("%d\n", numberOfCellsEqualToVal(myliste, int_test2));*/
    int partSelection, functionSelection, type, numberOfValues, index, category, size;
    char title[20], input[20];
    printf("Please enter which part of the project you want to test. \nFor columns : 1 \nFor Dataframe : 2 \nElse : 3\n");
    scanf("%d", &partSelection);
    if (partSelection == 1){
        printf("Please enter which function you want to use. \ncreate_column : 1\ninsert_value : 2\ndelete_column : 3\nprint_col : 4\noccurrence : 5\nvalueAtIndex : 6\nnumberOfValuesAboveSearchValue : 7\nnumberOfValuesUnderSearchValue : 8\nelse : 9\n");
        scanf("%d", &functionSelection);
        COLUMN *mycol = create_column("Test"); //for most tests
        if (functionSelection == 1){
            scanf("%s", title);
            COLUMN *mycolC = create_column(title);
            print_col(mycolC);
        }
        if (functionSelection == 2){
            printf("Enter number of values");
            scanf("%d", &numberOfValues);
            for (int i = 0; i<numberOfValues; i++){
                printf("Enter a value to insert :");
                fflush(stdin);
                fgets(input, 100, stdin);
                type = get_type(input);
                Data val;
                switch (type) {
                    case 1:
                        val.type = FLOAT_TYPE;
                        float resultat_f = atof(input);
                        val.value.float_type = resultat_f;
                        break;
                    case 2:
                        val.type = INT_TYPE;
                        int resultat_i = atoi(input);
                        val.value.int_type = resultat_i;
                        break;
                    case 3:
                        val.type = CHAR_TYPE;
                        val.value.char_type = input[0];
                        //A changer
                        break;
                    default:
                        val.value.char_type = ' ';
                }
                insert_value(mycol, val);
            }
            print_col(mycol);
        }
        Data int_test, int_test2, int_test3, char_test1, char_test2, float_test;
        int_test.type = INT_TYPE;
        int_test.value.int_type = 1;
        int_test2.type = INT_TYPE;
        int_test2.value.int_type = 2;
        int_test3.type = INT_TYPE;
        int_test3.value.int_type = 3;
        char_test1.type = CHAR_TYPE;
        char_test1.value.char_type = 'a';
        char_test2.type = CHAR_TYPE;
        char_test2.value.char_type = 'b';
        float_test.type = FLOAT_TYPE;
        float_test.value.float_type = 3.14;
        insert_value(mycol, int_test);
        insert_value(mycol, char_test1);
        insert_value(mycol, int_test2);
        insert_value(mycol, char_test2);
        insert_value(mycol, int_test3);
        insert_value(mycol, float_test);
        if (functionSelection == 3){
            print_col(mycol);
            delete_column(&mycol);
        }
        if (functionSelection == 4){
            print_col(mycol);
        }
        if (functionSelection == 5){
            printf("%d occurrence\n", occurrence(mycol, int_test2));
        }
        if (functionSelection == 6){
            printf("Enter index value : ");
            scanf("%d", &index);
            Data val = valueAtIndex(mycol, index);
            switch(val.type){
                case INT_TYPE :
                    printf("%d\n",val.value.int_type);
                    break;
                case CHAR_TYPE :
                    printf("%c\n", val.value.char_type);
                    break;
                case FLOAT_TYPE :
                    printf("%f\n",val.value.float_type);
                    break;
                case DOUBLE_TYPE :
                    printf("%lf\n",val.value.double_type);
                    break;
                default :
                    printf("ERROR : unknown type.\n");
                    break;
            }
            print_col(mycol);
        }
        if (functionSelection == 7){
            printf("%d values above search value\n", numberOfValuesAboveSearchValue(mycol, int_test));
        }
        if (functionSelection == 8){
            printf("%d values above search value\n", numberOfValuesUnderSearchValue(mycol, int_test2));
        }
    }
    if (partSelection == 2){
        printf("Please enter which function category you want to use.\nBasic : 1\nDisplay : 2\nNumber of ... : 3\nElse : 4\n");
        scanf("%d", &category);
        printf("Please enter which function you want to use : \n");
        Liste myliste=NULL;
        if (category == 1){
            printf("inputLinkedList : 1\nfillList : 2\naddRowToDataFrame : 3\nremoveRowFromDataFrame : 4\nremoveColumnFromDataFrame : 5\nrenamedColumn : 6\nrenamedColumn : 7\nexistsInDataframe : 8\naccessValueAtIndex : 9\nreplaceValueAtIndex : 10\n");
            scanf("%d", &functionSelection);
            if (functionSelection == 1){
                printf("Enter a number of columns");
                scanf("%d", &size);
                inputLinkedList(size, &myliste);
            }
        }
    }
    return 0;
}

