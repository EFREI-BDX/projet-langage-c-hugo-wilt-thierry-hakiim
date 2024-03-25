#include <stdio.h>
#include "columns.h"

int main() {
    COLUMN *mycol = create_column("My column");
    int Tab[4] = {3,2,1,5};
    mycol->data = &Tab;
    mycol->LOGICAL_SIZE=4;
    print_col(mycol);
    return 0;
}
