#include "dialogs.h"
#include "service_manager.h"
#include <string.h>
#include <stdio.h>

bool dl_prompt_new_master(GtkWindow *parent, char out_pass[], char recovery[]) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        "Set Master Password", parent, GTK_DIALOG_MODAL,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_OK", GTK_RESPONSE_OK, NULL
    );

    GtkWidget *box = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *entry_pass = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_pass), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_pass), "Master Password");

    GtkWidget *entry_pass2 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_pass2), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_pass2), "Confirm Password");

    GtkWidget *entry_recovery = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_recovery), "Recovery Answer");

    gtk_box_pack_start(GTK_BOX(box), entry_pass, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), entry_pass2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), entry_recovery, FALSE, FALSE, 5);
    gtk_widget_show_all(dialog);

    bool ok = false;
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        const char *p1 = gtk_entry_get_text(GTK_ENTRY(entry_pass));
        const char *p2 = gtk_entry_get_text(GTK_ENTRY(entry_pass2));
        const char *rec = gtk_entry_get_text(GTK_ENTRY(entry_recovery));

        if (strlen(p1) > 0 && strcmp(p1, p2) == 0 && strlen(rec) > 0) {
            strncpy(out_pass, p1, MAX_LEN-1);
            strncpy(recovery, rec, MAX_LEN-1);
            ok = true;
        }
    }

    gtk_widget_destroy(dialog);
    return ok;
}

bool dl_prompt_verify_master(GtkWindow *parent, char out_pass[]) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        "Enter Master Password", parent, GTK_DIALOG_MODAL,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_OK", GTK_RESPONSE_OK, NULL
    );

    GtkWidget *box = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
    gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 5);
    gtk_widget_show_all(dialog);

    bool ok = false;
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        strncpy(out_pass, gtk_entry_get_text(GTK_ENTRY(entry)), MAX_LEN-1);
        ok = true;
    }

    gtk_widget_destroy(dialog);
    return ok;
}

void dl_add_credential_dialog(GtkWidget *widget, gpointer user_data)
{
    AppState *app = (AppState*)user_data;

    GtkWidget *dialog =
        gtk_dialog_new_with_buttons(
            "Add Credential",
            GTK_WINDOW(app->window),
            GTK_DIALOG_MODAL,
            "_Cancel",
            GTK_RESPONSE_CANCEL,
            "_Add",
            GTK_RESPONSE_OK,
            NULL
        );

    GtkWidget *box =
        gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *entry_service = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_service),
                                   "Service");
    gtk_box_pack_start(GTK_BOX(box),
                       entry_service,
                       FALSE,
                       FALSE,
                       5);

    GtkWidget *entry_id = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_id),
                                   "ID");
    gtk_box_pack_start(GTK_BOX(box),
                       entry_id,
                       FALSE,
                       FALSE,
                       5);

    GtkWidget *entry_password = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_password),
                                   "Password");
    gtk_entry_set_visibility(GTK_ENTRY(entry_password),
                             FALSE);
    gtk_box_pack_start(GTK_BOX(box),
                       entry_password,
                       FALSE,
                       FALSE,
                       5);

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog))
        == GTK_RESPONSE_OK)
    {
        const char *service =
            gtk_entry_get_text(GTK_ENTRY(entry_service));

        const char *id =
            gtk_entry_get_text(GTK_ENTRY(entry_id));

        const char *password =
            gtk_entry_get_text(GTK_ENTRY(entry_password));

        if (strlen(service) > 0 &&
            strlen(id) > 0)
        {
            sm_add_credential(app,
                              service,
                              id,
                              password);
        }
    }

    gtk_widget_destroy(dialog);
}
