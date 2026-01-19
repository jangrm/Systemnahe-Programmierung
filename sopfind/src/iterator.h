#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef SOP_ITERATOR
#define SOP_ITERATOR

typedef enum {
    FI_FILE,
    FI_DIR,
    FI_SYMLINK,
    FI_OTHER,
    FI_UNKNOWN = 0
} FileType;

typedef struct {
    char *path;
    FileType type;
    mode_t mode;
    off_t size;
    time_t mtime;
} FileInfo;


typedef struct Stack {
     char *path;
     struct Stack *next;
     
} Stack;


int push(Stack **top , const char *path);
char *pop(Stack **top);

typedef struct Iterator Iterator;



Iterator *iterator_init(const char *start_path);
int iterator_next(Iterator *it, FileInfo *out);
void iterator_destroy(Iterator *it);
void fileinfo_free(FileInfo *info);




#endif







