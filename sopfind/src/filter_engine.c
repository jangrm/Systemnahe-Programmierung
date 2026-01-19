#include "filter.h"
#include <stdlib.h>
#include <string.h>

// Forward declarations for filter functions (implemented in filter_impl.c)
int filter_name(const char *path, const struct stat *st, void *data);
int filter_type(const char *path, const struct stat *st, void *data);
int filter_size(const char *path, const struct stat *st, void *data);
int filter_mtime(const char *path, const struct stat *st, void *data);

void add_filter(FilterNode **head, PredicateFunc pred, void *data) {
    FilterNode *new_node = malloc(sizeof(FilterNode));
    if (new_node == NULL) {
        return;
    }
    
    new_node->pred = pred;
    new_node->data = data;
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        FilterNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

int evaluate_filters(FilterNode *head, const char *path, const struct stat *st) {
    FilterNode *current = head;
    while (current != NULL) {
        if (current->pred == NULL) {
            return 0;
        }
        int passed = current->pred(path, st, current->data);
        if (passed == 0) {
            return 0;
        }
        current = current->next;
    }

    return 1;
}

void free_filters(FilterNode *head) {
    FilterNode *current = head;
    while (current != NULL) {
        FilterNode *next = current->next;
        if (current->data != NULL) {
            free(current->data);
        }
        free(current);
        current = next;
    }
}

void parse_argv_filters(FilterNode **filter_head, int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-name") == 0) {
            if (i + 1 < argc) {
                char *name_pattern = malloc(strlen(argv[i + 1]) + 1);
                if (name_pattern != NULL) {
                    strcpy(name_pattern, argv[i + 1]);
                    add_filter(filter_head, filter_name, (void *)name_pattern);
                }
                i++;
            }
        } else if (strcmp(argv[i], "-type") == 0) {
            if (i + 1 < argc) {
                char *type_char = malloc(sizeof(char));
                if (type_char != NULL) {
                    *type_char = argv[i + 1][0];
                    add_filter(filter_head, filter_type, (void *)type_char);
                }
                i++;
            }
        } else if (strcmp(argv[i], "-size") == 0) {
            if (i + 1 < argc) {
                size_filter_data *size_data = malloc(sizeof(size_filter_data));
                if (size_data != NULL) {
                    char *arg = argv[i + 1];
                    if (arg[0] == '+') {
                        size_data->mode = '+';
                        size_data->size = atol(arg + 1);
                    } else if (arg[0] == '-') {
                        size_data->mode = '-';
                        size_data->size = atol(arg + 1);
                    } else {
                        size_data->mode = '=';
                        size_data->size = atol(arg);
                    }
                    add_filter(filter_head, filter_size, (void *)size_data);
                }
                i++;
            }
        } else if (strcmp(argv[i], "-mtime") == 0) {
            if (i + 1 < argc) {
                mtime_filter_data *mtime_data = malloc(sizeof(mtime_filter_data));
                if (mtime_data != NULL) {
                    char *arg = argv[i + 1];
                    if (arg[0] == '+') {
                        mtime_data->mode = '+';
                        mtime_data->days = atol(arg + 1);
                    } else if (arg[0] == '-') {
                        mtime_data->mode = '-';
                        mtime_data->days = atol(arg + 1);
                    } else {
                        mtime_data->mode = '=';
                        mtime_data->days = atol(arg);
                    }
                    add_filter(filter_head, filter_mtime, (void *)mtime_data);
                }
                i++;
            }
        }
    }
}
