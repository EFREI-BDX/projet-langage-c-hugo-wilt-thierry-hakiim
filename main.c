#include <stdio.h>
#include "columns.h"
#include "CDataframe.h"

int main() {
    /*COLUMN *mycol = create_column("My column");
    insert_value(mycol, 5);
    insert_value(mycol, 3);
    insert_value(mycol, 3);
    printf("%d\n", mycol->LOGICAL_SIZE);
    printf("%d\n", mycol->PHYSICAL_SIZE);
    print_col(mycol);
    printf("%d\n", numberOfValuesAboveSearchValue(mycol, 3));
    printf("%d\n", numberOfValuesUnderSearchValue(mycol, 3));
    */


    inputFillCDataframe(createEmptyCDataframe(5));

    return 0;
}
