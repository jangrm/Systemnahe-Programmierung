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

} Iterator;




