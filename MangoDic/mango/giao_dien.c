#include "main.h"
#include "giao_dien.h"
#include "xu_ly_btree.h"
#include "string_deal.h"
#include "main.h"
#include "init.h"

#define EDIT 0
#define ADD 1

void load_giao_dien(){
  gtk_widget_show(main_window);
}

void load_dialog(){
  gtk_widget_show(GTK_WIDGET(loadDictPromptDialog));
}

void on_load_dict_yes(GtkWidget * widget,gpointer data){
    //ẩn cửa sổ loadDict
    // gtk_widget_hide(loadDictPromptDialog);
    gtk_widget_hide(GTK_WIDGET(loadDictPromptDialog));

    //NOTE HERE
    tao_dict_t(&currentDict,"EV_text_dict","dict_e_v.txt","BTree_dict.dat");
    wordListBuild();
}

void on_load_dict_no (GtkWidget *widget, gpointer data) {
    gtk_widget_hide(GTK_WIDGET(loadDictPromptDialog));
}

void on_window_main_destroy(){
	gtk_main_quit();
}


/* ABOUT ME BUTTON ****************/
void on_about_btn(){
    gtk_widget_show(GTK_WIDGET(about_me_window));
}

void on_about_close_btn(){
    gtk_widget_hide(GTK_WIDGET(about_me_window));
}
/* ABOUT ME BUTTON ****************/

/* ADD WORDS BUTTON (+) ********/
void on_add_btn(){

    if(currentDict.dict == NULL){ //Không có từ điển nào được tải (loaded).
        gtk_text_buffer_set_text(meaningViewBuff, "Loaded dictionary doesn't exist", -1);
        return;
    }
    control_mode = ADD;
    gtk_window_set_title (GTK_WINDOW(edit_add_words_window), "Add a word"); 
    //Ép kiểu edit_add_words_window từ Gtk_Widget về GTK_WINDOW, và thay đổi tên cửa sổ so với Glade ban đầu.
    gtk_widget_show(GTK_WIDGET(edit_add_words_window));

    gtk_entry_set_text (GTK_ENTRY(edit_add_words_entry), "");
    //xóa hết phần cũ ở edit_text_view_entry, thay bằng xâu "".

    gtk_text_buffer_set_text (edit_add_text_view_buffer,  "", -1);
    //xóa hết phần cũ ở edit_text_view_buffer, thay bằng toàn bộ (-1) xâu "".
 }

void on_edit_save(){
    GtkTextIter start,end;
    gchar *eng_entry;
    gchar *viet_buffer;
    gtk_widget_hide(GTK_WIDGET(edit_add_words_window));
    gtk_text_buffer_set_text(meaningViewBuff,"",-1);

    gtk_text_buffer_get_start_iter (edit_add_text_view_buffer, &start);
    gtk_text_buffer_get_end_iter (edit_add_text_view_buffer, &end);

    eng_entry = (gchar*) gtk_entry_get_text(GTK_ENTRY(edit_add_words_entry));
    viet_buffer = (gchar*) gtk_text_buffer_get_text(edit_add_text_view_buffer,&start,&end,1);
    // 1 is represent gboolean, TRUE, not embedded images.

    if(strlen(eng_entry) <=0 || strlen(viet_buffer) <=0) {
        gtk_text_buffer_set_text(meaningViewBuff,"Lack of \"WORD\" (in English) or \"MEANING\"(in Vietnamese)! \n",-1);
        gtk_text_buffer_insert_at_cursor(meaningViewBuff,"CANNOT ADD OR EDIT.\n",-1);
        return;
    }
    if(control_mode = ADD) gtk_text_buffer_set_text(meaningViewBuff,"Addition, done!:  ",-1);
    else if (control_mode = EDIT){
        dictionary_delete_word(currentDict.dict,eng_entry,meaningViewBuff);
        gtk_text_buffer_set_text(meaningViewBuff,"Edition, done!:  ",-1);
    }
    dictionary_add_word(currentDict.dict,eng_entry,viet_buffer,meaningViewBuff);
    gtk_text_buffer_insert_at_cursor(meaningViewBuff,eng_entry,-1);
    //in ra ở ngay vị trí con trỏ màn hình hiện tại toàn bộ nội dung biến eng_entry (do có -1)
    //meaningViewBuff is in main_window, attached to text_view
    // g_free(eng_entry);
    // g_free(viet_buffer);
} 

void on_edit_cancel(){
    gtk_widget_hide(GTK_WIDGET(edit_add_words_window));
}

/* ADD WORDS BUTTON (+) ********/

/* EDIT BUTTON ***********/
void on_edit_btn(){
   
    control_mode = EDIT;
    GtkTextIter start,end;
    gtk_text_buffer_get_start_iter (meaningViewBuff, &start);
    gtk_text_buffer_get_end_iter (meaningViewBuff, &end);

    gchar *word_entry_main = (gchar*)gtk_entry_get_text(GTK_ENTRY(lookupEntry));
    gchar *meaning_buffer_main = (gchar*)gtk_text_buffer_get_text(meaningViewBuff,&start,&end,1);

    if(strlen(word_entry_main) <= 0 || strlen(meaning_buffer_main) <=0){
        gtk_entry_set_text(GTK_ENTRY(lookupEntry),"");
        gtk_text_buffer_set_text(meaningViewBuff,"There's no word in Entry or Text View!\n",-1);
        gtk_text_buffer_insert_at_cursor(meaningViewBuff,"CANNOT EDIT",-1);
        return;
    }
    gtk_window_set_title(GTK_WINDOW(edit_add_words_window),"Edit an existed word");
    gtk_widget_show(GTK_WIDGET(edit_add_words_window));
    gtk_entry_set_text(GTK_ENTRY(edit_add_words_entry),word_entry_main);
    gtk_text_buffer_set_text(edit_add_text_view_buffer,meaning_buffer_main,-1);
    //Scan data in "lookupEntry" and "meaningViewBuff", then paste that data in "edit_add_words_entry","edit_add_text_view_buffer"

}

void close_word_edit(){

    gtk_widget_hide(GTK_WIDGET(edit_add_words_window));
    //DONE;
}
/* EDIT BUTTON ***********/

/* DELETE WORDS BUTTON *********/
void on_delete_btn(){ 
    //ask to delete a word (this button is in main window)
    chosen = (gchar*) gtk_entry_get_text(GTK_ENTRY(lookupEntry));
    if(strlen(chosen) > 0){
    gtk_widget_show(GTK_WIDGET(confirm_delete_dialog));
    } else {
        gtk_text_buffer_set_text(meaningViewBuff,"There's no word to be deleted!",-1);
    }
    //DONE
}   

void on_delete_btn_yes(){
    gtk_widget_hide(GTK_WIDGET(confirm_delete_dialog));
    dictionary_delete_word(currentDict.dict, chosen, meaningViewBuff);
    //DONE
}

void on_delete_btn_no(){
    gtk_widget_hide(GTK_WIDGET(confirm_delete_dialog));
    //DONE
}
/* DELETE WORDS BUTTON *********/

/* BACK - NEXT BUTTONS *******************/

void on_next_word_btn(){
    int store_next;
    char meaning_next[WORD_MAX_LEN];
    char word_next[WORD_MAX];
    gchar * moment_word = (gchar*) gtk_entry_get_text(GTK_ENTRY(lookupEntry));
    if(strlen(moment_word) <=0 ) {
        gtk_text_buffer_set_text(meaningViewBuff,"There's no word in Entry!\n",-1);
        gtk_text_buffer_insert_at_cursor(meaningViewBuff,"NEXT WORD DOESN'T EXIST!",-1);
        return;
    }

    //btpos(currentDict.dict,ZSTART);
    //BTint value;
    //strcpy(word_next,moment_word);
    //bfndky(currentDict.dict, moment_word, &value);
    //moment_word[value] = 0;

    int result_next = btseln(currentDict.dict,word_next,meaning_next,WORD_MAX_LEN*sizeof(char),&store_next);
    meaning_next[store_next] = '\0';
    if(result_next == 0){ //FOUND!
        gchar *uft8_meaning_next = g_utf8_make_valid(meaning_next,-1);
        gtk_entry_set_text (GTK_ENTRY(lookupEntry),word_next);
        gtk_text_buffer_set_text(meaningViewBuff,uft8_meaning_next,-1);
        gtk_text_buffer_insert_at_cursor(history_buff,word_next,-1);
        gtk_text_buffer_insert_at_cursor(history_buff,"\n",-1);
        g_free(uft8_meaning_next);
    }else{
        gtk_entry_set_text (GTK_ENTRY(lookupEntry), "");
        gtk_text_buffer_set_text(meaningViewBuff,"NOT FOUND",-1);
    }
    //g_free(moment_word); ---> CORE DUMPED!
}

void on_prev_word_btn(){
    gchar *moment_word_p;
    gchar *uft8_prev;
    int store_prev;
    char word_prev[WORD_MAX];
    char meaning_prev[WORD_MAX_LEN];
    
    moment_word_p = (gchar*) gtk_entry_get_text(GTK_ENTRY(lookupEntry));
    if(strlen(moment_word_p) <=0 ) {
        gtk_text_buffer_set_text(meaningViewBuff,"There's no word in Entry!\n",-1);
        gtk_text_buffer_insert_at_cursor(meaningViewBuff,"PREVIOUS WORD DOESN'T EXIST!",-1);
        return;
    }

    //btpos(currentDict.dict,ZSTART);
    strcpy(word_prev,moment_word_p);
    //BTint value;
    //bfndky(currentDict.dict, moment_word_p, &value);
    //moment_word_p[value] = 0;
    int result_prev = btselp(currentDict.dict,word_prev,meaning_prev,WORD_MAX_LEN*sizeof(char),&store_prev);

    meaning_prev[store_prev] = '\0';
    if(result_prev == 0){ //FOUND!
        uft8_prev = g_utf8_make_valid(meaning_prev,-1);
        gtk_entry_set_text (GTK_ENTRY(lookupEntry), word_prev);
        gtk_text_buffer_set_text(meaningViewBuff,uft8_prev,-1);
        gtk_text_buffer_insert_at_cursor(history_buff,word_prev,-1);
        gtk_text_buffer_insert_at_cursor(history_buff,"\n",-1);
        //gtk_entry_buffer_set_text (gtk_entry_get_buffer (lookupEntry), word_prev, strlen(word_prev));
        g_free(uft8_prev);
    }else{
        gtk_entry_set_text (GTK_ENTRY(lookupEntry), "");
        gtk_text_buffer_set_text(meaningViewBuff,"NOT FOUND",-1);
    }
}
/* BACK - NEXT BUTTONS ******************/

//main.h has every variables, so it's not neccesary to pass any variables in any functions.
//các hàm là riêng biệt. Khi gọi hàm on_edit_btn, do nó không hề liên quan đến on_add_btn nên bị lỗi, không biết biến edit_add_words_window là gì



void wordListBuild() 
{
    int i;
    BTint value;
    GtkTreeIter iter;

    char word[WORD_MAX_LEN];
    //gchar * g_word = gchar* gtk_entry_get_text(GTK_ENTRY(lookupEntry));

    // Clear old list
    gtk_list_store_clear (lookupEntryWordList);

    btpos(currentDict.dict, ZSTART);
    while(bnxtky(currentDict.dict, word, &value) == 0) {
        gtk_list_store_append(lookupEntryWordList, &iter);
        gtk_list_store_set(lookupEntryWordList, &iter, 0, word, -1);
    }
}
gboolean delete_find_store (GtkTreeModel *model,
                            GtkTreePath *path,
                            GtkTreeIter *iter,
                            gpointer data)
{
    gchar *item;
    gtk_tree_model_get(model, iter, 0, &item, -1);
    if(strcmp((char*)item,(char*)data) == 0)
    {
        gtk_list_store_remove (lookupEntryWordList,iter);
        g_free(item);
        return TRUE;
    }
    g_free(item);
    return FALSE;
}

void delete_store_entry_completion(const char * word)
{
    GtkTreeModel * model = gtk_entry_completion_get_model(lookupEntryCompletion);
    gtk_tree_model_foreach(model,(GtkTreeModelForeachFunc)delete_find_store,word);
}

void add_store_entry_completion(const char * word)
{
    //wordListBuild();
    //gtk_list_store_clear (lookupEntryWordList);
    // GtkTreeIter iter;
    // printf("ok1\n");
    // gtk_list_store_append(lookupEntryWordList, &iter);
    // printf("ok2\n");
    // gtk_list_store_set(lookupEntryWordList, &iter, 0, word, -1);
    // printf("ok3\n");
}

int suggestWordCmp(char * str, char * word) {
/*
so sanh tu 
0 str thu tu tu dien lon hon word 
1 str thu tu tu dien nho hon hoac bang word
*/
    if(strcmp(str,word) <= 0)return 1; 
    else return 0;
}

void dictfind()
{
    const gchar * searchEntryText = gtk_entry_buffer_get_text (gtk_entry_get_buffer (lookupEntry));
    char chuan_hoa_word[100];
    strcpy(chuan_hoa_word,searchEntryText);
    chuanhoa(chuan_hoa_word);
    char meaning[MEANING_MAX];
    int rsize;
    int check = btsel(currentDict.dict,(char *)chuan_hoa_word,meaning,sizeof(char)*MEANING_MAX,&rsize);
    if(rsize > MEANING_MAX*sizeof(char))
    {
        rsize = 0;
    }
    meaning[rsize] = '\0';
    if (check != 0)
    {
        gtk_text_buffer_set_text(meaningViewBuff, "Not found!", -1);
    }
    else 
    {
        gchar * utf_meaning = g_utf8_make_valid (meaning, -1);
        gtk_text_buffer_insert_at_cursor(history_buff,chuan_hoa_word,-1);
        gtk_text_buffer_insert_at_cursor(history_buff,"\n",-1);
        gtk_text_buffer_set_text(meaningViewBuff, utf_meaning, -1);
    }
}
void on_lookup_entry_activate() 
{   
    dictfind();
}
