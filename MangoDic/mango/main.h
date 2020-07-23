#ifndef MAIN_H
#define MAIN_H

#include "gtk/gtk.h"
#include "xu_ly_btree.h"

int control_mode;
#define WORD_MAX_LEN 100000

//Giai nhuy wrote
/* MAIN WINDOW *********************************/
GtkBuilder *builder;
GtkWidget  *main_window;
dict_t currentDict;
GtkEntry * lookupEntry;
GtkTextBuffer * meaningViewBuff;
GtkTextView *meaningView;
/* MAIN WINDOW *********************************/
//Giai nhuy wrote

// entry completion
GtkEntryCompletion *lookupEntryCompletion;
GtkListStore *lookupEntryWordList;

//Tuan Vu wrote
/* MANAGE DICT BUTTON **************************/
GtkWidget *manager_dict_window;
GtkWidget *add_dict_with_path_window;
GtkWidget *error_when_add_window;
/* MANAGE DICT BUTTON **************************/

/* ABOUT ME BUTTON *****************************/
GtkWidget *about_me_window;
/* ABOUT ME BUTTON *****************************/

/* ADD & EDIT BUTTON - SHARE GENERAL WINDOW ****/
GtkWidget *edit_add_words_window;

GtkEntry *edit_add_words_entry;

GtkTextBuffer *edit_add_text_view_buffer;
/* ADD & EDIT BUTTON - SHARE GENERAL WINDOW ****/

/* DELETE WORDS BUTTON *************************/
GtkDialog *confirm_delete_dialog;
/* DELETE WORDS BUTTON *************************/
//Tuan Vu wrote

// history
GtkTextView * history_view;
GtkTextBuffer * history_buff;

#endif
