#ifndef DIALOGS_H
#define DIALOGS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "app_state.h"

bool dl_prompt_new_master(GtkWindow *parent, char out_pass[], char recovery[]);
bool dl_prompt_verify_master(GtkWindow *parent, char out_pass[]);
void dl_add_credential_dialog(GtkWidget *widget, gpointer user_data);

#endif
