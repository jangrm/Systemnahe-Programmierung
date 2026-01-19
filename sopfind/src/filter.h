#ifndef FILTER_H
#define FILTER_H

#include <sys/stat.h>

typedef int (*PredicateFunc)(const char *path, const struct stat *st, void *data);

typedef struct FilterNode {
    PredicateFunc pred;
    void *data;
    struct FilterNode *next;
} FilterNode;

/* add a filter node with its predicate and associated data */
void add_filter(FilterNode **head, PredicateFunc pred, void *data);
/* evaluate all filters in the list for a given path/st */
int evaluate_filters(FilterNode *head, const char *path, const struct stat *st);
void free_filters(FilterNode *head);
void parse_argv_filters(FilterNode **filter_head, int argc, char *argv[]);

/* shared payload types for filters */
typedef struct {
    long size;
    char mode;  /* '+' = greater, '-' = less, '=' = equal */
} size_filter_data;

typedef struct {
    long days;
    char mode; /* '+' = older than, '-' = younger than, '=' = equal */
} mtime_filter_data;

int filter_name(const char *path, const struct stat *st, void *data);
int filter_type(const char *path, const struct stat *st, void *data);
int filter_size(const char *path, const struct stat *st, void *data);

#endif
