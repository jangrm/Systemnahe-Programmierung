#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef SOP_ITERATOR
#define SOP_ITERATOR

typedef enum {
    FI_FILE, // Reguläre Datei
    FI_DIR,  // Verzeichniss
    FI_SYMLINK, // Link
    FI_OTHER, // Sonderdateien
    FI_UNKNOWN = 0 //Fallback 
} FileType;

typedef struct {
    char *path; // Kompletter pfad 
    FileType type; // enum
    mode_t mode; // Dateirechte
    off_t size; // Dateigröße
    time_t mtime; // Letzte änderungszeit
} FileInfo;


typedef struct Stack {
     char *path;
     struct Stack *next;
     
} Stack;

int push(Stack **top , const char *path);
char *pop(Stack **top);

typedef struct Iterator Iterator;

Iterator *iterator_init(const char *start_path);
int iterator_next(Iterator *it);
void iterator_destroy(Iterator *it);
void fileinfo_free(FileInfo *info);




#endif







