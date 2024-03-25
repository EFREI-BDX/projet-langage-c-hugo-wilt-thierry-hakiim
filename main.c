#include <stdio.h>
#include "columns.h"

int main() {
    COLUMN *mycol = create_column("My column");
    printf("%d",mycol->PHYSICAL_SIZE);
    return 0;
}
