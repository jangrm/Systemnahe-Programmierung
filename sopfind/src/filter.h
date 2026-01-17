#ifndef FILTER_H
#define FILTER_H

typedef struct FilterNode {
    char *data;
    struct FilterNode *next;
} FilterNode;

#endif
