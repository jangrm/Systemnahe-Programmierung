#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef ITERATOR
#define ITERATOR

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


void  iterator(){


}



#endif







