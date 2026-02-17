#include "ui.h"
#include "dialogs.h"
#include <gtk/gtk.h>
#include <stdio.h>

AppState* ui_create_app(void) {
    AppState *app = g_malloc0(sizeof(AppState));

    app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app->window), "Password Vault");
    gtk_window_set_default_size(GTK_WINDOW(app->window), 400, 500);
    g_signal_connect(app->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(app->window), vbox);

    GtkWidget *btn_add = gtk_button_new_with_label("Add Credential");
    g_signal_connect(btn_add, "clicked", G_CALLBACK(dl_add_credential_dialog), app);
    gtk_box_pack_start(GTK_BOX(vbox), btn_add, FALSE, FALSE, 5);

    app->label_count = gtk_label_new("Services: 0");
    gtk_box_pack_start(GTK_BOX(vbox), app->label_count, FALSE, FALSE, 5);

    app->vbox_services = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), app->vbox_services, TRUE, TRUE, 5);

    return app;
}
