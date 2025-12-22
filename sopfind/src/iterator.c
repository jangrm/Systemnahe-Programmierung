#include "iterator.h"

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

static FileType classify(mode_t mode){
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


 if( strlen(base) == 0){
  return NULL;
 }
 int bonuslen = 0;
 int index = strlen(base) -1;
 
 if(base[index] != '/'){
     bonuslen = 1;
 }

 int total_len = len_base + len_name + bonuslen +1;

 char *final = malloc(total_len);
 if(final == NULL){
  return NULL;
 }

 
 memcpy(final,base,len_base);
 int pos = len_base;

 if(bonuslen == 1){
  final[pos++] = '/';
 }

 memcpy(final + pos,name,len_name);
 pos += len_name;


 final[pos] = '\0';

 return final;
}



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

void iterator_destroy(Iterator *it){
 if(it == NULL){return;}

 if(it->current_dir != NULL){
   closedir(it->current_dir);
   it->current_dir = NULL;
 }

 if(it->current_path != NULL){
   free(it->current_path);
   it->current_path = NULL;
 }

 char *p;

 while ((p = pop(&it->stack)) != NULL){
   free(p);
 }

 free(it);

}


void iterator_next(Iterator *it, FileInfo *out){
       out->path = NULL;

       while(true){
       
       // Wenn kein verzeichniss offen ist; nimme das nächste vom stack
       
       if(it->current_dir == NULL){
         char dirpath = pop(&it->stack);
	 if(dirpath == NULL){
	 return 0; // NIchts zu tun
	 }
 
	 // Directory öffnen und prüfen obs klappt; wenn nicht mache weiter
	 it->current_dir = opendir(dirpath);
	 if(it->current_dir == NULL){
           free(dirpath);
           continue;
	 }
         
	 // Path setzen
	 it->current_path = dirpath;
	 
	 // Eintrag lesen
	 entry = readdir(it->current_dir);
	 if(entry == NULL){
	  closedir(it->current_dir)
          it->current_dir = NULL;

	  free(it->current_path);
          it->current_path = NULL;

	  // nächstes Verzeichniss
	  continue;

	  // . und .. überspringen
	  
	  if(entry.name == "." || entry.name == ".."){
            continue;
	  }


          // Pfad bauen

	  fullpath = join_path(it->current_path, entry.name)
	  if(fullpath == NULL){
	   return -1;
	  }

	  // MEtadaten holen
	  if(lstat(fullpath, &st) == NULL){
	    free(fullpath);
	    continue;
	  }

	  // FileInfo füllen
	  out->path = fullpath;
	  out->mode = st.st_mode;
	  out->size = st.st_size;
	  out->mtime = st.st_mtime;
	  out->type = classify(st.st_mode);

	  // Wenn verzeichniss gefunden; für später auf den Stack
	  if(out->type == FI_DIR){
           push(&it->stack, fullpath);
	  }
          return 1;
	 }
       
       }
       
      }
       

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
     new->path = strdup(path); // strdup damit der pfad dem Stack gehört
     new->next = *top;

  if(new->path == NULL){free(new); return -1;}   
     *top = new;
     return 0;

}

char pop(Stack **top){
 if(*top == NULL){return NULL;}

   Stack *tmp = *top;
   char path = tmp->path;
   *top = *(tmp)->next;

   free(tmp);
   return path;
}

