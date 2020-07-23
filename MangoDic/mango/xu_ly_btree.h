#ifndef XU_LY_BTREE_H
#define XU_LY_BTREE_H

#define WORD_MAX 100000
#define MEANING_MAX 100000
#define DICTNAME_MAX 500
#define DICTPATH_MAX 500

#include "btree.h"
#include "gtk/gtk.h"

typedef struct dict_struct{
	BTA * dict;
	char name[DICTNAME_MAX];
	char path[DICTPATH_MAX];
}dict_t;


void them_tu(dict_t * dict,char * word,char * meaning);
void tao_dict_t(dict_t * dict,char * textName,char * dictName,char * dbName);
void mo_file(dict_t * dict);

/* DELETE BUTTON ********/
void dictionary_delete_word(BTA *dict, char *word, GtkTextBuffer *buffer);
gchar *chosen;
/* DELETE BUTTON ********/

/* ADD BUTTON ***********/
void dictionary_add_word(BTA *dict, char *word, char *meaning, GtkTextBuffer *buffer);
/* ADD BUTTON ***********/
char current_word[WORD_MAX];
char wordEditOrigin[WORD_MAX]; //???

#endif
