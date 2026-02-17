#ifndef UI_H
#define UI_H

#include "app_state.h"
#include "vault_storage.h"

AppState* ui_create_app(void);
void ui_refresh_services(AppState *app);

#endif // UI_H
