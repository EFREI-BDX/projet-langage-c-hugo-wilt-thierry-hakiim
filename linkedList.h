//
// Created by HugoW on 20/04/2024.
//

#ifndef PROJET_LANGAGE_C_LINKEDLIST_H
#define PROJET_LANGAGE_C_LINKEDLIST_H
#include "columns.h"

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

CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);
void fillCDataframe(CDATAFRAME *cdf);
void printCdataframeWithLimit(CDATAFRAME* cdf, int limitIndex);
void printCdataframe(CDATAFRAME* cdf);
void addLineToCdataFrame(CDATAFRAME *cdf, void **values);
void deleteLineFromCdataFrame(CDATAFRAME *cdf, int lineIndex);

#endif //PROJET_LANGAGE_C_LINKEDLIST_H
