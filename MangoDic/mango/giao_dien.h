#ifndef GIAO_DIEN_H
#define GIAO_DIEN_H

#include "xu_ly_btree.h"

GtkDialog * loadDictPromptDialog;
GtkWidget  * wordedit;

void load_giao_dien();
void on_window_main_destroy();
void load_dialog();
void on_load_dict_yes(GtkWidget * widget,gpointer data);
void on_load_dict_no(GtkWidget *widget, gpointer data);
void on_add_btn();



/* ABOUT ME BUTTON **********************/
void on_about_btn();
void on_about_close_btn();
/* ABOUT ME BUTTON **********************/

/* ADD WORDS BUTTON (+) *****************/
void on_add_btn();
void on_edit_cancel();
void on_edit_save();
/* ADD WORDS BUTTON (+) *****************/

/* DELETE WORDS BUTTON ******************/
void on_delete_btn();
void on_delete_btn_yes();
void on_delete_btn_no();
/* DELETE WORDS BUTTON ******************/

/* EDIT BUTTON **************************/
void on_edit_btn();
void close_word_edit();
/* EDIT BUTTON **************************/

/* BACK - NEXT BUTTONS ******************/
void on_next_word_btn();
void on_prev_word_btn();
/* BACK - NEXT BUTTONS ******************/

void wordListBuild();
void delete_store_entry_completion(const char * word);
void add_store_entry_completion(const char * word);

#endif
