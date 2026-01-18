#include <string.h>
#include <sys/stat.h>

int filter_name(const char *path, const struct stat *st, void *data)
{
    (void)st;
    const char *filename;
    const char *slash;
    
    slash = strrchr(path, '/');
    
    if (slash == NULL) {
        filename = path;
    } else {
        filename = slash + 1;
    }
    
    return strcmp(filename, (const char *)data) == 0;
}
