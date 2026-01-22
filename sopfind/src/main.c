#include <stdio.h>
#include <sys/stat.h>

#include "iterator.h"
#include "filter.h"
#include "cli.h"

int main(int argc, char *argv[]) {
    const char *start_path = ".";
    FilterNode *filter_head = NULL;

    int cli_rc = parse_cli(argc, argv, &start_path);
    if (cli_rc == 1) return 0;      // --help printed
    if (cli_rc < 0) return 2;       // CLI error

    parse_argv_filters(&filter_head, argc, argv);

    Iterator *it = iterator_init(start_path);
    if (!it) {
        fprintf(stderr, "Failed to initialize iterator for path: %s\n", start_path);
        free_filters(filter_head);
        return 1;
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
            printf("%s\n", info.path);
        }

        fileinfo_free(&info);
    }

    iterator_destroy(it);
    free_filters(filter_head);
    return 0;
}
