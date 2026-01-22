#define _POSIX_C_SOURCE 200809L
#include "iterator.h"

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>



static FileType classify(mode_t mode);
static char *join_path(const char *base, const char *name);
void *worker_thread(void *arg);



int push(Stack **top, const char *path);
char *pop(Stack **top);

typedef struct ResultNode {
    FileInfo info;
    struct ResultNode *next;
} ResultNode;

struct Iterator {
    Stack *stack;

    ResultNode *head;
    ResultNode *tail;

    pthread_mutex_t mutex;
    pthread_cond_t cond_work;
    pthread_cond_t cond_result;

    pthread_t *threads;
    int num_threads;
    int active_workers;


  
    bool finished;
    bool shutdown;
};






Iterator *iterator_init(const char *start_path){
    Iterator *it = malloc(sizeof(Iterator));
    if(it == NULL){ return NULL; }

    it->stack = NULL;
    it->head = NULL;
    it->tail = NULL;
    it->active_workers = 0;
    it->finished = false;
    it->shutdown = false;

    pthread_mutex_init(&it->mutex, NULL);
    pthread_cond_init(&it->cond_work, NULL);
    pthread_cond_init(&it->cond_result, NULL);


    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    if (nprocs < 1) nprocs = 4;
    it->num_threads = (int)nprocs;

    it->threads = malloc(sizeof(pthread_t) * it->num_threads);
    if (it->threads == NULL) {
        pthread_mutex_destroy(&it->mutex);
        pthread_cond_destroy(&it->cond_work);
        pthread_cond_destroy(&it->cond_result);
        free(it);
        return NULL;
    }


    if (push(&it->stack, start_path) == -1) {
        free(it->threads);
        pthread_mutex_destroy(&it->mutex);
        pthread_cond_destroy(&it->cond_work);
        pthread_cond_destroy(&it->cond_result);
        free(it);
        return NULL;
    }

    for (int i = 0; i < it->num_threads; i++) {
        pthread_create(&it->threads[i], NULL, worker_thread, it);
    }

    return it;
}

void iterator_destroy(Iterator *it){
    if(it == NULL){ return; }

    pthread_mutex_lock(&it->mutex);
    it->shutdown = true;
    pthread_cond_broadcast(&it->cond_work);
    pthread_cond_broadcast(&it->cond_result);
    pthread_mutex_unlock(&it->mutex);

    for (int i = 0; i < it->num_threads; i++) {
        pthread_join(it->threads[i], NULL);
    }
    free(it->threads);

    char *p;
    while ((p = pop(&it->stack)) != NULL){
        free(p);
    }

    while (it->head) {
        ResultNode *tmp = it->head;
        it->head = tmp->next;
        fileinfo_free(&tmp->info);
        free(tmp);
    }

    pthread_mutex_destroy(&it->mutex);
    pthread_cond_destroy(&it->cond_work);
    pthread_cond_destroy(&it->cond_result);

    free(it);
}

int iterator_next(Iterator *it, FileInfo *out){
    pthread_mutex_lock(&it->mutex);

    while (it->head == NULL) {
        if (it->finished && it->head == NULL) {
            pthread_mutex_unlock(&it->mutex);
            return 0;
        }
        if (it->shutdown) {
            pthread_mutex_unlock(&it->mutex);
            return -1;
        }
        pthread_cond_wait(&it->cond_result, &it->mutex);
    }

    ResultNode *node = it->head;
    it->head = node->next;
    if (it->head == NULL) {
        it->tail = NULL;
    }

    *out = node->info;
    free(node);

    pthread_mutex_unlock(&it->mutex);
    return 1;
}


void *worker_thread(void *arg) {
    Iterator *it = (Iterator *)arg;

    while (true) {
        pthread_mutex_lock(&it->mutex);

        while (it->stack == NULL && !it->shutdown && !it->finished) {
            if (it->active_workers == 0) {
                it->finished = true;
                pthread_cond_broadcast(&it->cond_work);
                pthread_cond_broadcast(&it->cond_result);
                pthread_mutex_unlock(&it->mutex);
                return NULL;
            }
            pthread_cond_wait(&it->cond_work, &it->mutex);
        }

        if (it->shutdown || it->finished) {
            pthread_mutex_unlock(&it->mutex);
            return NULL;
        }

        char *dirpath = pop(&it->stack);
        if (dirpath != NULL) {
            it->active_workers++;
        }

        pthread_mutex_unlock(&it->mutex);

        if (dirpath == NULL) continue;

        DIR *dir = opendir(dirpath);
        if (dir == NULL) {
            free(dirpath);
            pthread_mutex_lock(&it->mutex);
            it->active_workers--;
            if (it->stack == NULL && it->active_workers == 0) {
                it->finished = true;
                pthread_cond_broadcast(&it->cond_work);
                pthread_cond_broadcast(&it->cond_result);
            }
            pthread_mutex_unlock(&it->mutex);
            continue;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char *fullpath = join_path(dirpath, entry->d_name);
            if (fullpath == NULL) continue;

            struct stat st;
            if (lstat(fullpath, &st) != 0) {
                free(fullpath);
                continue;
            }

            FileInfo info;
            info.path = fullpath;
            info.mode = st.st_mode;
            info.size = st.st_size;
            info.mtime = st.st_mtime;
            info.type = classify(st.st_mode);

            pthread_mutex_lock(&it->mutex);

            ResultNode *node = malloc(sizeof(ResultNode));
            if (node) {
                node->info = info;
                node->next = NULL;
                if (it->tail) {
                    it->tail->next = node;
                } else {
                    it->head = node;
                }
                it->tail = node;
                pthread_cond_signal(&it->cond_result);
            } else {
                free(fullpath);
            }
            if (info.type == FI_DIR) {
                if (push(&it->stack, info.path) == 0) {
                     pthread_cond_signal(&it->cond_work);
                }
            }
            pthread_mutex_unlock(&it->mutex);
        }
        closedir(dir);
        free(dirpath);

        pthread_mutex_lock(&it->mutex);
        it->active_workers--;
        if (it->stack == NULL && it->active_workers == 0) {
            it->finished = true;
            pthread_cond_broadcast(&it->cond_work);
            pthread_cond_broadcast(&it->cond_result);}
        pthread_mutex_unlock(&it->mutex);
    }
    return NULL;
}


static FileType classify(mode_t mode){ //helper
    FileType type;
    if(S_ISDIR(mode)){
        type = FI_DIR;
    }else if(S_ISREG(mode)){
        type = FI_FILE;
    }else if(S_ISLNK(mode)){
        type = FI_SYMLINK;
    }else{
        type = FI_OTHER;
    }
    return type;
}

static char *join_path(const char *base, const char *name){
    if(base == NULL || name == NULL){
        return NULL;
    }

    int len_base = strlen(base);
    int len_name = strlen(name);

    if(strlen(base) == 0){
        return NULL;
    }
    int bonuslen = 0;
    int index = len_base - 1;

    if(base[index] != '/'){
        bonuslen = 1;
      }

    int total_len = len_base + len_name + bonuslen + 1;

    char *final = malloc(total_len);
    if(final == NULL){
        return NULL;
    }

    memcpy(final, base, len_base);
    int pos = len_base;

    if(bonuslen == 1){
        final[pos++] = '/';
    }

    memcpy(final + pos, name, len_name);
    pos += len_name;
    final[pos] = '\0';

    return final;
}

void fileinfo_free(FileInfo *info){
    if(info == NULL){return;}

    if(info->path != NULL){
        free(info->path);
        info->path = NULL;
    }
}

int push(Stack **top, const char *path){

    Stack *new = malloc(sizeof(Stack));

    if(new == NULL){return -1;}
    
    new->path = strdup(path);
    new->next = *top;

    if(new->path == NULL){
        free(new);
        return -1;
    }
    *top = new;
    return 0;
}

char *pop(Stack **top){

    if(*top == NULL){return NULL;}

    Stack *tmp = *top;
    char *path = tmp->path;
    *top = tmp->next;

    free(tmp);
    return path;
}