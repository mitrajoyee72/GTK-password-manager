#include "service_manager.h"
#include "vault_storage.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void sm_view_service(GtkWidget *widget, gpointer user_data);

void sm_add_credential(AppState *app,
                       const char *service,
                       const char *username,
                       const char *password)
{
    // Save to file
    vs_save_credential(service, username, password);

    // Store in memory
    Credential *c = malloc(sizeof(Credential));
    strncpy(c->service, service, MAX_LEN - 1);
    strncpy(c->username, username, MAX_LEN - 1);
    strncpy(c->password, password, MAX_LEN - 1);

    app->credentials = g_list_append(app->credentials, c);

    // Check if this service button already exists
    GList *l;
    gboolean exists = FALSE;

    for (l = app->credentials; l != NULL; l = l->next) {
        Credential *existing = l->data;

        if (existing != c &&
            strcmp(existing->service, service) == 0)
        {
            exists = TRUE;
            break;
        }
    }

    // If first credential of this service → create button
    if (!exists) {
        GtkWidget *btn = gtk_button_new_with_label(service);

        g_signal_connect(btn,
                         "clicked",
                         G_CALLBACK(sm_view_service),
                         app);

        gtk_box_pack_start(GTK_BOX(app->vbox_services),
                           btn,
                           FALSE,
                           FALSE,
                           5);

        gtk_widget_show_all(app->vbox_services);
    }

    // Update count label
    char buf[64];
    snprintf(buf,
             sizeof(buf),
             "Total Credentials: %d",
             g_list_length(app->credentials));

    gtk_label_set_text(GTK_LABEL(app->label_count), buf);
}

static void sm_view_service(GtkWidget *widget, gpointer user_data)
{
    AppState *app = (AppState*)user_data;

    const char *service =
        gtk_button_get_label(GTK_BUTTON(widget));

    GtkWidget *dialog =
        gtk_dialog_new_with_buttons(
            service,
            GTK_WINDOW(app->window),
            GTK_DIALOG_MODAL,
            "_Close",
            GTK_RESPONSE_CLOSE,
            NULL
        );

    GtkWidget *box =
        gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GList *l;

    for (l = app->credentials; l != NULL; l = l->next) {

        Credential *c = l->data;

        if (strcmp(c->service, service) == 0) {

            char buf[256];

            snprintf(buf,
                     sizeof(buf),
                     "ID: %s\nPassword: %s",
                     c->username,
                     c->password);

            GtkWidget *label = gtk_label_new(buf);

            gtk_box_pack_start(GTK_BOX(box),
                               label,
                               FALSE,
                               FALSE,
                               5);
        }
    }

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
