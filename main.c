#include <stdio.h>
#include "columns.h"
#include "CDataframe.h"

int main() {
    COLUMN *mycol = create_column("My column");
    Data int_test, int_test2, int_test3;
    int_test.type = INT_TYPE;
    int_test.value.int_type = 1;
    int_test2.type = INT_TYPE;
    int_test2.value.int_type = 2;
    int_test3.type = INT_TYPE;
    int_test3.value.int_type = 3;

    insert_value(mycol, int_test);
    insert_value(mycol, int_test2);
    insert_value(mycol, int_test3);
    printf("%d\n", mycol->LOGICAL_SIZE);
    printf("%d\n", mycol->PHYSICAL_SIZE);
    print_col(mycol);
    printf("%d occurrence\n", occurrence(mycol, int_test));
    printf("%d values above search value\n", numberOfValuesAboveSearchValue(mycol, int_test));
    printf("%d values above search value\n", numberOfValuesUnderSearchValue(mycol, int_test2));

    /*
    tableau CDataframe = createEmptyCDataframe();
    inputFillCDataframe(&CDataframe);
     */


    return 0;
}
