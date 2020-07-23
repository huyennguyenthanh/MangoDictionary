#include "init.h"


// Lookup a match result from lookup field completion
int on_lookup_match_selected(GtkEntryCompletion *widget,
               GtkTreeModel       *model,
               GtkTreeIter        *iter,
               gpointer            user_data) {
    gchar *word;
    gtk_tree_model_get(model, iter, 0, &word, -1);

    // update lookup field
    gtk_entry_buffer_set_text(gtk_entry_get_buffer(lookupEntry), word, -1);

    dictfind((char *)word);
    return TRUE;
}

gboolean lookupEntryMatchFunc(GtkEntryCompletion *completion,
                                    const gchar *key,
                                    GtkTreeIter *iter,
                                    gpointer user_data) {
    GtkTreeModel *model = gtk_entry_completion_get_model(completion);
    gchar *item;
    gtk_tree_model_get(model, iter, 0, &item, -1);
    gboolean ans = (suggestWordCmp((char *)key, (char *)item) == 1) ? TRUE : FALSE;
    g_free(item);
    return ans;
}

void init()
{
	//main window
  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "GUI/main5.glade", NULL);
  gtk_builder_connect_signals(builder, NULL);
  main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main-window"));

  //dialog
  loadDictPromptDialog = GTK_DIALOG(gtk_builder_get_object(builder, "load-dict-prompt"));

 	//lookup entry
 	lookupEntry = GTK_ENTRY(gtk_builder_get_object(builder, "lookup-entry"));

  //lookup completion
  lookupEntryCompletion = gtk_entry_completion_new();
  lookupEntryWordList = gtk_list_store_new(1, G_TYPE_STRING);
  gtk_entry_completion_set_model(lookupEntryCompletion, GTK_TREE_MODEL(lookupEntryWordList));
  gtk_entry_completion_set_match_func(lookupEntryCompletion, (GtkEntryCompletionMatchFunc)lookupEntryMatchFunc, NULL, NULL);
  gtk_entry_set_completion(GTK_ENTRY(lookupEntry), lookupEntryCompletion);
  gtk_entry_completion_set_text_column(lookupEntryCompletion, 0);
  g_signal_connect(lookupEntryCompletion, "match-selected", G_CALLBACK(on_lookup_match_selected), NULL);

 	//meaning view
  meaningViewBuff = gtk_text_buffer_new(NULL); 
  meaningView = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "meaning-view"));
  gtk_text_view_set_buffer (meaningView, meaningViewBuff);

  //manager dict
  manager_dict_window = GTK_WIDGET(gtk_builder_get_object(builder, "dict-manager-window"));
  add_dict_with_path_window = GTK_WIDGET(gtk_builder_get_object(builder,"dict-manager-add-dict-form"));
  error_when_add_window = GTK_WIDGET(gtk_builder_get_object(builder,"dict-add-error-msg"));

  //about me 
  about_me_window = GTK_WIDGET(gtk_builder_get_object(builder,"about-window"));

  //add and edit
  edit_add_words_window = GTK_WIDGET(gtk_builder_get_object(builder,"word-edit"));
  edit_add_words_entry = GTK_ENTRY(gtk_builder_get_object(builder,"word-edit-word"));
  edit_add_text_view_buffer = GTK_TEXT_BUFFER(gtk_builder_get_object(builder,"word-edit-meaning-buff"));

  //delete
  confirm_delete_dialog = GTK_DIALOG(gtk_builder_get_object(builder, "del-current-word-prompt"));

  //history
  history_view = GTK_WIDGET(gtk_builder_get_object(builder,"history-view"));
  history_buff = gtk_text_buffer_new(NULL);
  gtk_text_view_set_buffer (history_view,history_buff);

}
