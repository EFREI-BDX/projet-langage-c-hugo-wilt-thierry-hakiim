//
// Created by HugoW on 20/05/2024.
//

#ifndef PROJET_LANGAGE_C_SORT_H
#define PROJET_LANGAGE_C_SORT_H
#include "linkedList.h"
#define ASC 0
#define DESC 1

void sort(COLUMN* col,int sort_dir);
void swap(unsigned long long *a,unsigned long long *b);
void insertionSort(COLUMN* col,unsigned int sort_dir, unsigned int size);
unsigned int partition (COLUMN* col, unsigned int left, unsigned int right, int sort_dir);
void quickSort(COLUMN* col, unsigned int left, unsigned int right, int sort_dir);
void displayColByIndex(COLUMN *col);
void eraseIndex(COLUMN *col);
int checkIndex(COLUMN *col);
void updateIndex(COLUMN *col);
int searchValueInColumn(COLUMN *col, void *val);
int compareValues(COL_TYPE *a, COL_TYPE *b, ENUM_TYPE type);

#endif //PROJET_LANGAGE_C_SORT_H
