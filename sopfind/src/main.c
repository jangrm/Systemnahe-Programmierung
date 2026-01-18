#include <stdio.h>
#include <string.h>
#include "iterator.h"
#include "filter.h"

int main(int argc,char *argv[]){
    const char *start_path = "/";
    FilterNode *filter_head = NULL;

    // Parse -p argument if present
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            start_path = argv[i + 1];
            break;
        }
    }

    parse_argv_filters(&filter_head, argc, argv);

    Iterator *it = iterator_init(start_path);
    if(!it){
      fprintf(stderr, "Failed to initialize iterator for path: %s\n", start_path);
      return 1;
    }


    FileInfo info;

    while (1){
      int r = iterator_next(it, &info);
      if(r == 0){
         break;
      }
      if(r < 0){
         fprintf(stderr, "Iterator error\n");
         break;
      }
      printf("%s\n", info.path);

      fileinfo_free(&info);
    
    }
    iterator_destroy(it);
    free_filters(filter_head);
    return 0;

}



