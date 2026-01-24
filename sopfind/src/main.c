#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "iterator.h"
#include "filter.h"
#include "cli.h"

static void process_path(const char *path, FilterNode *filter_head) {
    Iterator *it = iterator_init(path);
    if (!it) {
        fprintf(stderr, "Failed to initialize iterator for path: %s\n", path);
        return;
    }

    FileInfo info;
    while (1) {
        int r = iterator_next(it, &info);
        if (r == 0) break;
        if (r < 0) {
            fprintf(stderr, "Iterator error\n");
            break;
        }

        struct stat st = {0};
        st.st_mode  = info.mode;
        st.st_size  = info.size;
        st.st_mtime = info.mtime;

        int passes = 1;
        if (filter_head != NULL) {
            passes = evaluate_filters(filter_head, info.path, &st);
        }

        if (passes) {
            fprintf(stdout, "%s\n", info.path);
        }

        fileinfo_free(&info);
    }

    iterator_destroy(it);
}

int main(int argc, char *argv[]) {
    const char *start_path = ".";
    int use_stdin = 0;
    FilterNode *filter_head = NULL;

    int cli_rc = parse_cli(argc, argv, &start_path, &use_stdin);
    if (cli_rc == 1) return 0;      // --help printed
    if (cli_rc < 0) return 2;       // CLI error

    parse_argv_filters(&filter_head, argc, argv);

    if (use_stdin) {
        char line[4096];
        while (fgets(line, sizeof(line), stdin) != NULL) {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }
            if (strlen(line) > 0) {
                process_path(line, filter_head);
            }
        }
    } else {
        process_path(start_path, filter_head);
    }

    free_filters(filter_head);
    return 0;
}
