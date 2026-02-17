#ifndef APP_STATE_H
#define APP_STATE_H

#include <gtk/gtk.h>
#include "credential.h"

typedef struct {
    GtkWidget *window;
    GtkWidget *vbox_services;
    GtkWidget *label_count;
    char session_master[MAX_LEN];
    char recovery_answer[MAX_LEN];
    GList *credentials; // List of Credential*
} AppState;

#endif
