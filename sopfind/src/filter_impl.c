#include <string.h>
#include <sys/stat.h>
#include <fnmatch.h>

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
    
    return fnmatch((const char *)data, filename, 0) == 0;
}
