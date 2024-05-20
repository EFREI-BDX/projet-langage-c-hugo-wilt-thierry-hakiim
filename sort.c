#include "sort.h"
#include "columns.h"

void swap(unsigned long long *a, unsigned long long *b) {
    unsigned long long temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(COLUMN *col, unsigned int sort_dir, unsigned int size) {
    unsigned long long key;
    int j;
    for (int i = 1; i < size; i++) {
        key = col->index[i];
        j = i - 1;
        while (j >= 0 && ((sort_dir == ASC && col->index[j] > key) || (sort_dir == DESC && col->index[j] < key))) {
            col->index[j + 1] = col->index[j];
            j--;
        }
        col->index[j + 1] = key;
    }
    col->valid_index = 1;
}

unsigned int partition(COLUMN *col, unsigned int left, unsigned int right, int sort_dir) {
    if (right >= col->index_size) {
        printf("Error: Index out of bounds\n");
        return -1;
    }
    unsigned long long pivot = col->index[right];
    unsigned int i = left - 1;
    for (unsigned int j = left; j < right; j++) {
        if (j < col->index_size && col->data[col->index[j]] != NULL && pivot < col->index_size && col->data[pivot] != NULL) {
            int comparison;
            switch (col->column_type) {
                case UINT_TYPE:
                    comparison = (col->data[col->index[j]]->uint_type - col->data[pivot]->uint_type);
                    break;
                case INT_TYPE:
                    comparison = (col->data[col->index[j]]->int_type - col->data[pivot]->int_type);
                    break;
                case CHAR_TYPE:
                    comparison = (col->data[col->index[j]]->char_type - col->data[pivot]->char_type);
                    break;
                case FLOAT_TYPE:
                    comparison = (col->data[col->index[j]]->float_type - col->data[pivot]->float_type) > 0 ? 1 : -1;
                    break;
                case DOUBLE_TYPE:
                    comparison = (col->data[col->index[j]]->double_type - col->data[pivot]->double_type) > 0 ? 1 : -1;
                    break;
                case STRING_TYPE:
                    comparison = strcmp(col->data[col->index[j]]->string_type, col->data[pivot]->string_type);
                    break;
                default:
                    comparison = 0;
            }
            if ((sort_dir == ASC && comparison <= 0) || (sort_dir == DESC && comparison >= 0)) {
                i++;
                swap(&col->index[i], &col->index[j]);
            }
        }
    }
    if (i + 1 < col->index_size) {
        swap(&col->index[i + 1], &col->index[right]);
    }
    return i + 1;
}

void quickSort(COLUMN *col, unsigned int low, unsigned int high, int sort_dir) {
    if (low < high) {
        unsigned int pi = partition(col, low, high, sort_dir);
        if (pi != -1 && pi < col->index_size) {
            quickSort(col, low, pi - 1, sort_dir);
            quickSort(col, pi + 1, high, sort_dir);
        }
    }
    col->valid_index = 1;
}

void sort(COLUMN *col, int sort_dir) {
    if (col == NULL) {
        printf("The column is NULL\n");
        return;
    }
    if (col->index == NULL) {
        col->index = (unsigned long long *)malloc(col->LOGICAL_SIZE * sizeof(unsigned long long));
        for (unsigned int i = 0; i < col->LOGICAL_SIZE; i++) {
            col->index[i] = i;
        }
        col->index_size = col->LOGICAL_SIZE;
    }
    if (col->valid_index == 0) {
        quickSort(col, 0, col->index_size - 1, sort_dir);
    } else if (col->valid_index == -1) {
        insertionSort(col, sort_dir, col->index_size);
    }
    col->sort_dir = sort_dir;
}

void displayColByIndex(COLUMN *col) {
    if (col == NULL) {
        printf("The column is NULL\n");
        return;
    }
    printf("Title: %s\n", col->title);
    char string[REALOC_SIZE];
    for (unsigned long long int i = 0; i < col->index_size; i++) {
        if (i < col->index_size && col->data[col->index[i]] != NULL) {
            printf("[%llu] ", i);
            switch (col->column_type) {
                case STRING_TYPE:
                    if (col->data[col->index[i]]->string_type == NULL) {
                        printf("NULL\n");
                    } else {
                        printf("%s\n", col->data[col->index[i]]->string_type);
                    }
                    break;
                default:
                    convertValue(col, col->index[i], string, sizeof(string));
                    printf("%s\n", string);
            }
        } else {
            printf("Error: Index out of bounds or data is NULL\n");
        }
    }
}

void eraseIndex(COLUMN *col){
    if (col == NULL) {
        printf("No work to do :P\n");
    }
    else {
        free(col->index);
        col->index = NULL;
        col->valid_index = 0;
    }
}

int checkIndex(COLUMN *col){
    if (col == NULL) {
        printf("No work to do :P\n");
    }
    return col->valid_index;
}

void updateIndex(COLUMN *col){
    int valueIndex;
    if (col == NULL){
        printf("No work to do\n");
    } else {
        scanf("%d", &valueIndex);
        col->valid_index = valueIndex;
    }
}



int compareValues(COL_TYPE *a, COL_TYPE *b, ENUM_TYPE type) {
    switch (type) {
        case UINT_TYPE:
            return (a->uint_type > b->uint_type) - (a->uint_type < b->uint_type);
        case INT_TYPE:
            return (a->int_type > b->int_type) - (a->int_type < b->int_type);
        case CHAR_TYPE:
            return (a->char_type > b->char_type) - (a->char_type < b->char_type);
        case FLOAT_TYPE:
            return (a->float_type > b->float_type) - (a->float_type < b->float_type);
        case DOUBLE_TYPE:
            return (a->double_type > b->double_type) - (a->double_type < b->double_type);
        case STRING_TYPE:
            return strcmp(a->string_type, b->string_type);
        case STRUCT_TYPE:
            return (a->struct_type > b->struct_type) - (a->struct_type < b->struct_type);
        default:
            return 0;
    }
}


int searchValueInColumn(COLUMN *col, void *val) {
    if (col == NULL || val == NULL) {
        printf("The column or value is NULL\n");
        return -1;
    } else if  (col->valid_index == -1) {
        printf("Invalid index :c\n");
        return -1;
    } else {
        int left = 0;
        int right = col->index_size - 1;
        COL_TYPE search_val;
        switch (col->column_type) {
            case UINT_TYPE:
                search_val.uint_type = *(unsigned int *)val;
                break;
            case INT_TYPE:
                search_val.int_type = *(int *)val;
                break;
            case CHAR_TYPE:
                search_val.char_type = *(char *)val;
                break;
            case FLOAT_TYPE:
                search_val.float_type = *(float *)val;
                break;
            case DOUBLE_TYPE:
                search_val.double_type = *(double *)val;
                break;
            case STRING_TYPE:
                search_val.string_type = (char *)val;
                break;
            case STRUCT_TYPE:
                search_val.struct_type = val;
                break;
            default:
                return -1;
        }
        while (left <= right) {
            int mid = left + (right - left) / 2;
            COL_TYPE *mid_val = col->data[col->index[mid]];
            int cmp = compareValues(mid_val, &search_val, col->column_type);
            if (cmp == 0) {
                return 1;
            } else if (cmp < 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return 0;
}