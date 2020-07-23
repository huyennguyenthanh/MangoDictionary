#ifndef INIT_H
#define INIT_H

#include "gtk/gtk.h"
#include "main.h"
#include "giao_dien.h"

void init();
int on_lookup_match_selected(GtkEntryCompletion *widget,
               GtkTreeModel       *model,
               GtkTreeIter        *iter,
               gpointer            user_data);

gboolean lookupEntryMatchFunc(GtkEntryCompletion *completion,
                                    const gchar *key,
                                    GtkTreeIter *iter,
                                    gpointer user_data);

#endif