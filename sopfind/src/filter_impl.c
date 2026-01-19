#include <string.h>
#include <sys/stat.h>
#include <fnmatch.h>
#include <time.h>

typedef struct {
    long size;
    char mode;  // '+' = größer als, '-' = kleiner als, '=' = genau
} size_filter_data;

typedef struct {
    long days;
    char mode;  // '+' = älter als, '-' = jünger als, '=' = genau
} mtime_filter_data;

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

int filter_type(const char *path, const struct stat *st, void *data)
{
    (void)path;
    char type = *(char *)data;
    
    if (type == 'f') {
        return S_ISREG(st->st_mode);
    } else if (type == 'd') {
        return S_ISDIR(st->st_mode);
    }
    
    return 0;
}

int filter_size(const char *path, const struct stat *st, void *data)
{
    (void)path;
    size_filter_data *size_data = (size_filter_data *)data;
    long file_size = (long)st->st_size;
    
    if (size_data->mode == '+') {
        return file_size > size_data->size;
    } else if (size_data->mode == '-') {
        return file_size < size_data->size;
    } else {
        return file_size == size_data->size;
    }
}

int filter_mtime(const char *path, const struct stat *st, void *data)
{
    (void)path;
    mtime_filter_data *mtime_data = (mtime_filter_data *)data;

    time_t now = time(NULL);
    if (now == (time_t)-1) {
        return 0;
    }

    long diff_days = (long)((now - st->st_mtime) / 86400);

    if (mtime_data->mode == '+') {
        return diff_days > mtime_data->days;
    } else if (mtime_data->mode == '-') {
        return diff_days < mtime_data->days;
    }

    return diff_days == mtime_data->days;
}
