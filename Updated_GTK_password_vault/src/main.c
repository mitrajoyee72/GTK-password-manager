#include <gtk/gtk.h>
#include "ui.h"
#include "master_auth.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    AppState *app = ui_create_app();

    if (!ma_prompt_master_password(app)) {
        g_print("User cancelled master password setup/verification.\n");
        g_free(app);
        return 0;
    }

    gtk_widget_show_all(app->window);
    gtk_main();

    g_free(app);
    return 0;
}
