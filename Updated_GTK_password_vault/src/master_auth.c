#include "master_auth.h"
#include "vault_storage.h"
#include "dialogs.h"
#include <string.h>
#include <gtk/gtk.h>
#include <stdio.h>

bool ma_prompt_master_password(AppState *app) {
    if (!vs_master_exists()) {
        if (!dl_prompt_new_master(GTK_WINDOW(app->window), app->session_master, app->recovery_answer))
            return false;
        vs_save_master(app->session_master, app->recovery_answer);
        return true;
    } else {
        char input[MAX_LEN];
        if (!dl_prompt_verify_master(GTK_WINDOW(app->window), input))
            return false;
        if (vs_verify_master(input)) {
            strncpy(app->session_master, input, MAX_LEN-1);
            return true;
        } else {
            GtkWidget *msg = gtk_message_dialog_new(GTK_WINDOW(app->window),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_OK,
                                                    "Incorrect Master Password!");
            gtk_dialog_run(GTK_DIALOG(msg));
            gtk_widget_destroy(msg);
            return false;
        }
    }
}

bool ma_change_master_password(AppState *app) {
    char current[MAX_LEN];
    if (!dl_prompt_verify_master(GTK_WINDOW(app->window), current))
        return false;

    if (vs_verify_master(current)) {
        char new_master[MAX_LEN], recovery[MAX_LEN];
        if (!dl_prompt_new_master(GTK_WINDOW(app->window), new_master, recovery))
            return false;
        vs_save_master(new_master, recovery);
        strncpy(app->session_master, new_master, MAX_LEN-1);
        strncpy(app->recovery_answer, recovery, MAX_LEN-1);
        return true;
    } else {
        GtkWidget *msg = gtk_message_dialog_new(GTK_WINDOW(app->window),
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK,
                                                "Incorrect Current Password!");
        gtk_dialog_run(GTK_DIALOG(msg));
        gtk_widget_destroy(msg);
        return false;
    }
}
