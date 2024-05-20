//
// Created by Administrateur on 20/05/2024.
//

#include "sort.h"
void swap(unsigned long long *a,unsigned long long *b){
    unsigned long long temp =*a;
    *a=*b;
    *b=temp;
}
void insertionSort(COLUMN* col, unsigned int sort_dir, unsigned int size){
    unsigned long long key;
    int j;
    for(int i = 1; i < size; i++){
        key = col->index[i];
        j = i - 1;
        while (j >= 0 && ((sort_dir == ASC && col->index[j] > key) || (sort_dir == DESC && col->index[j] < key))){
            col->index[j + 1] = col->index[j];
            j--;
        }
        col->index[j + 1] = key;
    }
}
unsigned int partition(COLUMN* col, unsigned int low, unsigned int high, int sort_dir){
    if (high >= col->index_size) {
        printf("Error: Index out of bounds\n");
        return -1;
    }
    unsigned long long pivot = col->index[high];
    unsigned int i = low - 1;
    for(unsigned int j = low; j < high; j++){
        if (j < col->index_size && col->data[col->index[j]] != NULL && pivot < col->index_size && col->data[pivot] != NULL) {
            if ((sort_dir == ASC && col->data[col->index[j]]->int_type <= col->data[pivot]->int_type) ||
                (sort_dir == DESC && col->data[col->index[j]]->int_type >= col->data[pivot]->int_type)) {
                i++;
                swap(&col->index[i], &col->index[j]);
            }
        }
    }
    if (i + 1 < col->index_size) {
        swap(&col->index[i + 1], &col->index[high]);
    }
    return i + 1;
}
void quickSort(COLUMN* col, unsigned int low, unsigned int high, int sort_dir){
    if(low < high){
        unsigned int pi = partition(col, low, high, sort_dir);
        if(pi != -1 && pi < col->index_size) {
            quickSort(col, low, pi - 1, sort_dir);
            quickSort(col, pi + 1, high, sort_dir);
        }
    }
}


void sort(COLUMN* col, int sort_dir) {
    if (col == NULL) {
        printf("The column is NULL");
        return;
    }
    if (col->valid_index == 0) {
        quickSort(col, 0, col->index_size - 1, sort_dir);
    } else if (col->valid_index == -1) {
        insertionSort(col, sort_dir, col->index_size);
    }
}
void displayColByIndex(COLUMN* col) {
    if (col == NULL) {
        printf("The column is NULL");
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
                    convert_value(col, col->index[i], string, sizeof(string));
                    printf("%s\n", string);
            }
        } else {
            printf("Error: Index out of bounds or data is NULL\n");
        }
    }
}