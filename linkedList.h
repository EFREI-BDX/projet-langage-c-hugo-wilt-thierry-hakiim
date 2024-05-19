//
// Created by HugoW on 20/04/2024.
//

#ifndef PROJET_LANGAGE_C_LINKEDLIST_H
#define PROJET_LANGAGE_C_LINKEDLIST_H
#include "columns.h"
#include "stdbool.h" //To check if value exists


typedef struct lnode_{
    COLUMN *data;
    struct lnode_ *prev;
    struct lnode_ *next;
}LNODE;

typedef struct list_ {
    LNODE *head;
    LNODE *tail;
} LIST;
typedef LIST CDATAFRAME;

CDATAFRAME *createCdataframe(ENUM_TYPE *cdftype, int size);
#define MAX_TITLE_NAME_SIZE 50

CDATAFRAME* makeCell(ENUM_TYPE type, char *title);
void deleteColumn(CDATAFRAME *cdf, char *colName);
void deleteCdataframe(CDATAFRAME** cdf);
int getCdataframeColsSize(CDATAFRAME *cdf);
void fillCDataframe(CDATAFRAME *cdf);
void hardFillCDataframe(CDATAFRAME *cdf);
void printCdataframe(CDATAFRAME *cdf);
void printCdataframeWithLimit(CDATAFRAME* cdf, int limitIndex);
void addColumn(CDATAFRAME *cdf, char *title, ENUM_TYPE type);
void changeColumnTitle(CDATAFRAME *cdf, char *oldTitle, char *newTitle);
bool valueExistsInColumn(COLUMN *col, void *value);
int valueExists(CDATAFRAME *cdf, void *value);
void* accessCellValue(CDATAFRAME *cdf, unsigned long long rowIndex, unsigned long long colIndex);
void replaceCellValue(CDATAFRAME *cdf, unsigned int rowIndex, unsigned int colIndex, void *newValue);
void printColumnNames(CDATAFRAME *cdf);
void printNumberOfRows(CDATAFRAME *cdf);
void printNumberOfColumns(CDATAFRAME *cdf);
int occurrenceValInDataframe(CDATAFRAME *cdf, void* value);
int countValuesGreaterThan(CDATAFRAME *cdf, void *value);


LIST *inputLinkedList(int size, LIST *myliste);
void fillList(char* title, LIST* liste); //fill the list
void hardFillLinked(LIST* liste);
void displayList(LIST liste); //display dataframe
void display(const CDATAFRAME *temp); //display data of column (called in displayList)
void displayLinkedLinesWithLimit(LIST liste, void* limit);
void displayLines(void* *limit, const CDATAFRAME *temp);
void displayLinkedColumnsWithLimit(LIST liste, char* title);
void displayColumns(char* title, const CDATAFRAME *temp);
void addRowToDataFrame(LIST liste);
void removeRowFromDataFrame(LIST liste, int indexToRemove);
void remove_element(void* *data, int index, int array_length);
void removeColumnFromDataFrame(LIST* liste, char* titleToRemove);
void renameColumn(LIST* liste, char* oldTitle, char* newTitle);
int existsInDataframe(LIST liste, void* valToCompare);
void accessValueAtIndex(LIST liste, int lineNumber, int columnNumber);
void replaceValueAtIndex(LIST liste, int lineNumber, int columnNumber);
void displayColumnsNames(LIST liste);
int numberOfLines(LIST liste);
int numberOfColumns(LIST liste);
int numberOfCellsEqualToVal(LIST liste, void* valToCompare);
int numberOfCellsUnderVal(LIST liste, void* valToCompare);
int numberOfCellsAboveVal(LIST liste, void* valToCompare);
#endif //PROJET_LANGAGE_C_LINKEDLIST_H
