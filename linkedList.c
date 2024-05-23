//
// Created by HugoW on 20/04/2024.
//

#include "linkedList.h"

// Listes chainées

CDATAFRAME *createCdataframe(ENUM_TYPE *cdftype, int size){
    CDATAFRAME *cdf = (CDATAFRAME *)malloc(sizeof(CDATAFRAME));
    if (cdf==NULL) {
        return NULL;
    }
    cdf->head = NULL;
    cdf->tail = NULL;
    for (int i = 0; i < size; i++) {
        char title[REALOC_SIZE];
        snprintf(title, 20, "Column %d", i+1); // Generate a title for each column
        COLUMN *col = createColumnPart2(cdftype[i], title);
        if(col == NULL){
            return NULL;
        }
        LNODE *node=(LNODE*)malloc(sizeof(LNODE));
        if(node==NULL){
            return NULL;
        }
        node->data=col;
        if (cdf->head == NULL) {
            node->prev = NULL;
            node->next = NULL;
            cdf->head = node;
            cdf->tail = node;
        }else{
            node->prev=cdf->tail;
            node->next=NULL;
            cdf->tail->next = node;
            cdf->tail = node;
        }
    }
    return cdf;
}

void deleteCdataframe(CDATAFRAME** cdf) {
    if (cdf == NULL || *cdf == NULL) return;
    LNODE* current = (*cdf)->head;
    LNODE* next;
    while (current != NULL) {
        deleteColumnPart2(&current->data);
        next = current->next;
        free(current);
        current = next;
    }
    (*cdf)->head = NULL;
    (*cdf)->tail = NULL;
    free(*cdf);
    *cdf = NULL;
}

void deleteColumn(CDATAFRAME *cdf, char *colName) {
    if (cdf == NULL || colName == NULL) return;
    LNODE* current = cdf->head;
    LNODE* prev = NULL;
    while (current != NULL) {
        COLUMN* col = current->data;
        if (strcmp(col->title, colName) == 0) {
            if (prev == NULL) {
                cdf->head = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == cdf->tail) {
                cdf->tail = prev;
            }
            deleteColumnPart2(&col);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int getCdataframeColsCize(CDATAFRAME *cdf) {
    int cpt = 0;
    LNODE* current = cdf->head;
    while (current != NULL) {
        cpt++;
        current = current->next;
    }
    return cpt;
}

void fillCDataframe(CDATAFRAME *cdf) {
    if (cdf == NULL || cdf->head == NULL) return;
    LNODE* current = cdf->head;
    while (current != NULL) {
        COLUMN* col = current->data;
        printf("Number of values for column %s: ", col->title);
        int numberOfValues;
        scanf("%d", &numberOfValues);
        col->LOGICAL_SIZE = numberOfValues;
        col->data = (COL_TYPE**)malloc(numberOfValues * sizeof(COL_TYPE*));
        for (int i = 0; i < numberOfValues; i++) {
            col->data[i] = (COL_TYPE*)malloc(sizeof(COL_TYPE));
            printf("Enter value %d for column %s: ", i + 1, col->title);
            switch (col->column_type) {
                case UINT_TYPE:
                    scanf("%u", &col->data[i]->uint_type);
                    break;
                case INT_TYPE:
                    scanf("%d", &col->data[i]->int_type);
                    break;
                case CHAR_TYPE:
                    scanf(" %c", &col->data[i]->char_type);
                    break;
                case FLOAT_TYPE:
                    scanf("%f", &col->data[i]->float_type);
                    break;
                case DOUBLE_TYPE:
                    scanf("%lf", &col->data[i]->double_type);
                    break;
                case STRING_TYPE:
                    col->data[i]->string_type = (char*)malloc(100 * sizeof(char));
                    scanf("%s", col->data[i]->string_type);
                    break;
                case STRUCT_TYPE:
                    printf("Struct input not implemented.\n");
                    break;
                case NULLVAL:
                    printf("NULL");
                    break;
                default:
                    printf("Unknown type.\n");
                    break;
            }
        }
        current = current->next;
    }
}

void hardFillCDataframe(CDATAFRAME *cdf) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL) {
        int numberOfValues = 0;
        printf("Number of values for column %s: ", current->data->title);
        scanf("%d", &numberOfValues);
        double d = 3.33;
        if (current->data->column_type == DOUBLE_TYPE || current->data->column_type == FLOAT_TYPE ){
            for (int i = 1; i <= numberOfValues; i++) {
                insertValuePart2(current->data, &d);
                d = d*3;
            }
        } else{
            for (int i = 1; i <= numberOfValues; i++) {
                insertValuePart2(current->data, &i);
            }
        }
        current = current->next;
    }
}

void printCdataframe(CDATAFRAME* cdf) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL) {
        printCol(current->data);
        current = current->next;
    }
}

void printCdataframeWithLimit(CDATAFRAME* cdf, int limitIndex) {
    int cpt =0;
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL && cpt<limitIndex) {

        printCol(current->data);
        current = current->next;
        cpt+=1;
    }
}

void addColumn(CDATAFRAME *cdf, char *title, ENUM_TYPE type) {
    if (cdf == NULL || title == NULL) return;
    COLUMN *new_col = (COLUMN *)malloc(sizeof(COLUMN));
    new_col->title = strdup(title);
    new_col->LOGICAL_SIZE = 0;
    new_col->PHYSICAL_SIZE = 0;
    new_col->column_type = type;
    new_col->data = NULL;
    new_col->index = NULL;
    LNODE *new_node = (LNODE *)malloc(sizeof(LNODE));
    new_node->data = new_col;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (cdf->tail == NULL) {
        cdf->head = new_node;
        cdf->tail = new_node;
    } else {
        cdf->tail->next = new_node;
        new_node->prev = cdf->tail;
        cdf->tail = new_node;
    }
}

void changeColumnTitle(CDATAFRAME *cdf, char *oldTitle, char *newTitle) {
    if (cdf == NULL || oldTitle == NULL || newTitle == NULL) {
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL) {
        COLUMN* col = current->data;
        if (strcmp(col->title, oldTitle) == 0) {
            free(col->title);
            col->title = strdup(newTitle);
            return;
        }
        current = current->next;
    }
}

int valueExists(CDATAFRAME *cdf, void *value) {
    if (cdf == NULL || value == NULL) return 0;

    LNODE *current = cdf->head;
    while (current != NULL) {
        if (valueExistsInColumn(current->data, value)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

bool valueExistsInColumn(COLUMN *col, void *value) { //Bool :O
    if (col == NULL || value == NULL) return false;
    for (unsigned int i = 0; i < col->LOGICAL_SIZE; i++) {
        switch (col->column_type) {
            case UINT_TYPE:
                if (*(unsigned int*)col->data[i] == *(unsigned int*)value) {
                    return true;
                }
                break;
            case INT_TYPE:
                if (*(int*)col->data[i] == *(int*)value) {
                    return true;
                }
                break;
            case CHAR_TYPE:
                if (*(char*)col->data[i] == *(char*)value) {
                    return true;
                }
                break;
            case FLOAT_TYPE:
                if (*(float*)col->data[i] == *(float*)value) {
                    return true;
                }
                break;
            case DOUBLE_TYPE:
                if (*(double*)col->data[i] == *(double*)value) {
                    return true;
                }
                break;
            case STRING_TYPE:
                if (strcmp((char*)col->data[i], (char*)value) == 0) {
                    return true;
                }
                break;
            case STRUCT_TYPE:
                break;
            default:
                // Unknown type :c
                break;
        }
    }
    return false;
}


void* accessCellValue(CDATAFRAME *cdf, unsigned long long rowIndex, unsigned long long colIndex) {
    if (cdf == NULL){
        return NULL;
    }
    LNODE *current = cdf->head;
    unsigned long long colCount = 0;
    while (current != NULL && colCount < colIndex) {
        current = current->next;
        colCount++;
    }
    if (current == NULL){
        return NULL;
    }
    if (rowIndex >= current->data->LOGICAL_SIZE) {
        return NULL;
    }
    return current->data->data[rowIndex];
}

void replaceCellValue(CDATAFRAME *cdf, unsigned int rowIndex, unsigned int colIndex, void *newValue) {
    if (cdf == NULL) return;
    LNODE *current = cdf->head;
    unsigned int colCount = 0;
    while (current != NULL && colCount < colIndex) {
        current = current->next;
        colCount++;
    }
    if (current == NULL) return;
    if (rowIndex >= current->data->LOGICAL_SIZE) return;
    switch (current->data->column_type) {
        case UINT_TYPE:
            *(unsigned int *)current->data->data[rowIndex] = *(unsigned int *)newValue;
            break;
        case INT_TYPE:
            *(int *)current->data->data[rowIndex] = *(int *)newValue;
            break;
        case CHAR_TYPE:
            *(char *)current->data->data[rowIndex] = *(char *)newValue;
            break;
        case FLOAT_TYPE:
            *(float *)current->data->data[rowIndex] = *(float *)newValue;
            break;
        case DOUBLE_TYPE:
            *(double *)current->data->data[rowIndex] = *(double *)newValue;
            break;
        case STRING_TYPE:
            free(current->data->data[rowIndex]->struct_type);
            current->data->data[rowIndex]->string_type = strdup((char *)newValue);
            break;
        case STRUCT_TYPE:
            break;
        default:
            break;
    }
}

void printColumnNames(CDATAFRAME *cdf) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL) {
        printf("%s\n", current->data->title);
        current = current->next;
    }
}

void printNumberOfRows(CDATAFRAME *cdf) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    unsigned int rowCount = current->data->LOGICAL_SIZE;
    printf("Number of rows: %u\n", rowCount);
}

void printNumberOfColumns(CDATAFRAME *cdf) {
    if (cdf == NULL || cdf->head == NULL) {
        printf("Empty CDATAFRAME\n");
        return;
    }
    LNODE* current = cdf->head;
    unsigned int columnCount = 0;
    while (current != NULL) {
        columnCount++;
        current = current->next;
    }
    printf("Number of columns: %u\n", columnCount);
}

int occurrenceValInDataframe(CDATAFRAME *cdf, void* value) {
    int cpt =0;
    if (cdf == NULL || cdf->head == NULL) {
        return cpt;
    }
    LNODE* current = cdf->head;
    unsigned int columnCount = 0;
    while (current != NULL) {
        cpt += occurrencePart2(current->data, value);
        current = current->next;
    }
    return cpt;
}


int countValuesGreaterThan(CDATAFRAME *cdf, void *value) {
    if (cdf == NULL || cdf->head == NULL || value == NULL) {
        printf("Empty CDATAFRAME or invalid value\n");
        return 0;
    }
    int count = 0;
    LNODE *current = cdf->head;
    ENUM_TYPE valueType = determineType(value);
    while (current != NULL) {
        COLUMN *col = current->data;
        if (col->column_type == valueType) {
            count += numberOfValuesAboveSearchValuePart2(col, value);
        }
        current = current->next;
    }
    return count;
}

int countValuesLesserThan(CDATAFRAME *cdf, void *value) {
    if (cdf == NULL || cdf->head == NULL || value == NULL) {
        printf("Empty CDATAFRAME or invalid value\n");
        return 0;
    }
    int count = 0;
    LNODE *current = cdf->head;
    ENUM_TYPE valueType = determineType(value);
    while (current != NULL) {
        COLUMN *col = current->data;
        if (col->column_type == valueType) {
            count += numberOfValuesUnderSearchValuePart2(col, value);
        }
        current = current->next;
    }
    return count;
}


ENUM_TYPE determineType(const void *value) {
    if (value == NULL) {
        return NULLVAL;
    }
    if (*(unsigned int *)value == (unsigned int)*(unsigned int *)value) {
        return UINT_TYPE;
    } else if (*(int *)value == (int)*(int *)value) {
        return INT_TYPE;
    } else if (*(char *)value == (char)*(char *)value) {
        return CHAR_TYPE;
    } else if (*(float *)value == (float)*(float *)value) {
        return FLOAT_TYPE;
    } else if (*(double *)value == (double)*(double *)value) {
        return DOUBLE_TYPE;
    } else if (strcmp((char *)value, (char *)value) == 0) {
        return STRING_TYPE;
    }
    return NULLVAL;
}