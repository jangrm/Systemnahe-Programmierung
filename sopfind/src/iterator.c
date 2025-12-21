#include "iterator.h"

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


struct Iterator {
 Stack *stack;
 DIR *current_dir;
 char *current_path;

};



Iterator *iterator_init(const char *start_path){
 Iterator *new = malloc(sizeof(Iterator));
 if(new == NULL){return NULL;}
	 new->*stack = NULL;
	 new->*current_dir = NULL;
	 new->*current_path = NULL;
  
 int i = push(&new->stack, start_path);
 if(i == -1){
  free(new);
  return NULL;
 }
 return new;
}


