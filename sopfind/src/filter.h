#ifndef FILTER_H
#define FILTER_H

#include <sys/stat.h>

typedef int (*PredicateFunc)(const char *path, const struct stat *st, void *data);

typedef struct FilterNode {
    void *data;
    struct FilterNode *next;
} FilterNode;

void add_filter(FilterNode **head, void *data);
int evaluate_filters(FilterNode *head, PredicateFunc predicate, const char *path, const struct stat *st);
void free_filters(FilterNode *head);

#endif
