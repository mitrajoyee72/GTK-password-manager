#ifndef MASTER_AUTH_H
#define MASTER_AUTH_H

#include <stdbool.h>
#include "app_state.h"

bool ma_prompt_master_password(AppState *app);
bool ma_change_master_password(AppState *app);

#endif
