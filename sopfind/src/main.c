#include <stdio.h>
#include <string.h>
#include "iterator.h"

int main(int argc,char *argv[]){
    const char *start_path = "/";


    if (argc == 1){
	// Default
    }else if(argc == 3 && strcmp(argv[1], "-p")== 0){
      start_path = argv[2];
    } else {
      fprintf(stderr, "Usage: [-p <path>] \n");
      return 1;
    }

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
    return 0;

}



