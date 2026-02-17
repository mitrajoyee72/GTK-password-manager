#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include "app_state.h"
#include <stdbool.h>

void sm_add_credential(AppState *app,
                       const char *service,
                       const char *username,
                       const char *password);

#endif
