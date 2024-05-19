#include <stdio.h>
#include "columns.h"
#include "linkedList.h"


/*Data getInput(int type, char *input);

int main() {
    int partSelection, functionSelection, type, numberOfValues, index, category, size;
    char title[20], input[20];
    printf("Please enter which part of the project you want to test. \nFor columns : 1 \nFor Dataframe : 2 \nElse : 3\n");
    scanf("%d", &partSelection);
    if (partSelection == 1){
        printf("Please enter which function you want to use. \ncreate_column : 1\ninsert_value : 2\ndelete_column : 3\nprint_col : 4\noccurrence : 5\nvalueAtIndex : 6\nnumberOfValuesAboveSearchValue : 7\nnumberOfValuesUnderSearchValue : 8\nelse : 9\n");
        scanf("%d", &functionSelection);
        COLUMN *mycol = create_column("Test"); //for most tests
        if (functionSelection == 1){
            printf("Enter a title : ");
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
        Data int_test, int_test2, int_test3, char_test1, char_test2, float_test, string_test;
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
        string_test.type = STRING_TYPE;
        strcpy(&(string_test.value.string_type), "Test");
        insert_value(mycol, int_test);
        insert_value(mycol, char_test1);
        insert_value(mycol, int_test2);
        insert_value(mycol, char_test2);
        insert_value(mycol, int_test3);
        insert_value(mycol, float_test);
        //insert_value(mycol, string_test.value.string_type);
        if (functionSelection == 3){
            print_col(mycol);
            delete_column(&mycol);
            printf("Column was deleted");
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
                case STRING_TYPE :
                    printf("%s\n",&(val.value.string_type));
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
            printf("fillList : 1\nhardFillLinked : 2\naddRowToDataFrame : 3\nremoveRowFromDataFrame : 4\nremoveColumnFromDataFrame : 5\nrenamedColumn : 6\nexistsInDataframe : 7\naccessValueAtIndex : 8\nreplaceValueAtIndex : 9\n");
            scanf("%d", &functionSelection);
            if (functionSelection == 1){
                size = 3;
                Liste myliste2 = NULL;
                inputLinkedList(size, &myliste2);
                displayList(myliste2);
            }
            if (functionSelection == 2){
                hardFillLinked(&myliste);
                displayList(myliste);
            }
            if (functionSelection == 3){
                hardFillLinked(&myliste);
                addRowToDataFrame(myliste);
                displayList(myliste);
            }
            if (functionSelection == 4){
                hardFillLinked(&myliste);
                printf("Enter index value : ");
                scanf("%d", &index);
                removeRowFromDataFrame(myliste, index);
                displayList(myliste);
            }
            if (functionSelection == 5){
                char titleR;
                hardFillLinked(&myliste);
                printf("Enter title: ");
                scanf("%s", &titleR);
                removeColumnFromDataFrame(&myliste, &titleR);
                displayList(myliste);
            }
            if (functionSelection == 6){
                hardFillLinked(&myliste);
                char oldTitle[20], newTitle[20];
                printf("Enter old title : ");
                scanf("%s", oldTitle);
                printf("Enter new title : ");
                scanf("%s", newTitle);
                printf("%s %s\n", oldTitle, newTitle);
                //renameColumn(&myliste,oldTitle, newTitle);
                displayList(myliste);
            }
            if (functionSelection == 7){
                hardFillLinked(&myliste);
                printf("Enter a value to compare with :");
                Data val = getInput(type, input);
                printf("1 if value exists 0 otherwise : %d",existsInDataframe(myliste, val));
            }
            if (functionSelection == 8){
                hardFillLinked(&myliste);
                int lineNumber, columnNumber;
                printf("Enter column number : ");
                scanf("%d", &columnNumber);
                printf("Enter line number : ");
                scanf("%d", &lineNumber);
                accessValueAtIndex(myliste, lineNumber, columnNumber);
                displayList(myliste);
            }
            if (functionSelection == 9){
                hardFillLinked(&myliste);
                int lineNumber, columnNumber;
                printf("Enter column number : ");
                scanf("%d", &columnNumber);
                printf("Enter line number : ");
                scanf("%d", &lineNumber);
                replaceValueAtIndex(myliste, lineNumber, columnNumber);
                displayList(myliste);
            }
        }
        if (category == 2){
            printf("displayList : 1\ndisplayLinkedLinesWithLimit : 2\ndisplayLinkedColumnsWithLimit : 3\ndisplayColumnsNames : 4\n");
            scanf("%d", &functionSelection);
            if (functionSelection == 1){
                hardFillLinked(&myliste);
                displayList(myliste);
            }
            if (functionSelection == 2){
                hardFillLinked(&myliste);
                printf("Enter a value to compare with :");
                Data val = getInput(type, input);
                displayLinkedLinesWithLimit(myliste, val);
            }
            if (functionSelection == 3){
                hardFillLinked(&myliste);
                char titleL;
                printf("Enter a title :");
                scanf("%s", title);
                displayLinkedColumnsWithLimit(myliste, title);
            }
            if (functionSelection == 4){
                hardFillLinked(&myliste);
                displayColumnsNames(myliste);
            }
        }
        if (category == 3){
            printf("numberOfLines : 1\nnumberOfColumns : 2\nnumberOfCellsEqualToVal : 3\nnumberOfCellsUnderVal : 4\nnumberOfCellsAboveVal : 5\n");
            scanf("%d", &functionSelection);
            if (functionSelection == 1){
                hardFillLinked(&myliste);
                printf("There are %d lines", numberOfLines(myliste));
            }
            if (functionSelection == 2){
                hardFillLinked(&myliste);
                printf("There are %d columns", numberOfColumns(myliste));
            }
            if (functionSelection == 3){
                hardFillLinked(&myliste);
                printf("Enter a value to compare with :");
                Data val = getInput(type, input);
                printf("There are %d cells equal to val", numberOfCellsEqualToVal(myliste, val));
            }
            if (functionSelection == 4){
                hardFillLinked(&myliste);
                printf("Enter a value to compare with :");
                Data val = getInput(type, input);
                printf("There are %d cells under val", numberOfCellsUnderVal(myliste, val));
            }
            if (functionSelection == 5){
                hardFillLinked(&myliste);
                printf("Enter a value to compare with :");
                Data val = getInput(type, input);
                printf("There are %d cells above val", numberOfCellsAboveVal(myliste, val));
            }

        }
    } if (partSelection == 3){
        COLUMN *mycol = createcolumnPart2(CHAR_TYPE, "My Column");
        char a = 'A', c = 'C';
        insertvaluePart2(mycol, &a);
        insertvaluePart2(mycol, NULL);
        insertvaluePart2(mycol, &c);

    }
    return 0;
}
Data getInput(int type, char *input) {
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
    return val;
}*/
int main(){
    char str[5];
    COLUMN *mycol = createcolumnPart2(INT_TYPE, "My column");
    int a = 52, b = 44, c = 15, d = 18, e = 15, f = 15, g =12, h = 3;
    char k = 'a';
    insertvaluePart2(mycol, &a);
    insertvaluePart2(mycol, &b);
    insertvaluePart2(mycol, &c);
    insertvaluePart2(mycol, &d);
    insertvaluePart2(mycol, &e);
    insertvaluePart2(mycol, &f);
    insertvaluePart2(mycol, &g);
    insertvaluePart2(mycol, &h);
    insertvaluePart2(mycol, &k);
    print_col(mycol);
    printf("%d ", occurrencePart2(mycol, &k));
    printf("%d ", numberOfValuesAboveSearchValuePart2(mycol, &k));
    printf("%d\n", numberOfValuesUnderSearchValuePart2(mycol, &k));
    printValueAtIndex(mycol, 3);
    return 0;
}

