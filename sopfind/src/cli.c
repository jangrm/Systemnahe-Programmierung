// File: sopfind/src/cli.c
#include "cli.h"
#include <stdio.h>
#include <string.h>

void print_usage(const char *progname) {
    fprintf(stdout, "Usage: %s [-p path] [--stdin] [filters...]\n", progname);
    fprintf(stdout, "  -p, --path PATH    Start path for iteration (default: .)\n");
    fprintf(stdout, "  --stdin            Read paths from stdin (one per line)\n");
    fprintf(stdout, "  -h, --help         Show this help message\n");
}

int parse_cli(int argc, char *argv[], const char **start_path, int *use_stdin) {
    if (start_path == NULL || use_stdin == NULL) {
        return -1;
    }

    *start_path = ".";
    *use_stdin = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 1;
        }

        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--path") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: missing argument for %s\n", argv[i]);
                return -1;
            }
            *start_path = argv[i + 1];
            i++;
            continue;
        }

        if (strcmp(argv[i], "--stdin") == 0) {
            *use_stdin = 1;
            continue;
        }
    }

    return 0;
}

