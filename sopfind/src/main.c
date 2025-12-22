#include <stdio.h>
#include "iterator.h"

int main(){
    Iterator *it = iterator_init(".");
    if(it == NULL){
     printf(stderr, "iterator_init failed \n");
    }

    FileInfo info;

    while (1){
     int r = iterator_next(it, &info)
     if(r == 0){
       break;
     }

     if(r < 0){
      printf(stderr, "iterator_next error \n");
     }

     printf("%s\n", info.path);

     fileinfo_free(&info);
    
    
    
    
    
    }
    iterator_destroy(it);
    return 0;

}



