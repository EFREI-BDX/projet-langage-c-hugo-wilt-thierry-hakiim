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
int countValuesLesserThan(CDATAFRAME *cdf, void *value);
ENUM_TYPE determineType(void *value);
void addLineToCdataFrame(CDATAFRAME *cdf, void **values);
void deleteLineFromCdataFrame(CDATAFRAME *cdf, int lineIndex);
#endif //PROJET_LANGAGE_C_LINKEDLIST_H
