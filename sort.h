//
// Created by Administrateur on 20/05/2024.
//

#ifndef PROJET_LANGAGE_C_SORT_H
#define PROJET_LANGAGE_C_SORT_H
#include "columns.h"
#include "linkedList.h"
#define ASC 0
#define DESC 1

void sort(COLUMN* col,int sort_dir);
void swap(unsigned long long *a,unsigned long long *b);
void insertionSort(COLUMN* col,unsigned int sort_dir, unsigned int size);
unsigned int partition (COLUMN* col,unsigned int low, unsigned int high, int sort_dir);
void quickSort(COLUMN* col, unsigned int low, unsigned int high, int sort_dir);
void displayColByIndex(COLUMN *col);

#endif //PROJET_LANGAGE_C_SORT_H
