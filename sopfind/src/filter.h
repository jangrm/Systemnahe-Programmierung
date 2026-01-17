#ifndef FILTER_H
#define FILTER_H

#include <sys/stat.h>

typedef int (*PredicateFunc)(const char *path, const struct stat *st, void *data);

typedef struct FilterNode {
    char *data;
    struct FilterNode *next;
} FilterNode;

void add_filter(FilterNode **head, const char *data);
int evaluate_filters(FilterNode *head, PredicateFunc predicate, const char *path, const struct stat *st);

#endif
