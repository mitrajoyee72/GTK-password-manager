#ifndef VAULT_STORAGE_H
#define VAULT_STORAGE_H

#include "credential.h"
#include <stdbool.h>
#include <glib.h>

// Vault files
#define MASTER_FILE "vault_master.dat"
#define CREDENTIAL_FILE "vault_creds.dat"

// Master password
bool vs_master_exists(void);
bool vs_save_master(const char *master, const char *recovery);
bool vs_verify_master(const char *master);
bool vs_check_recovery(const char *answer);
bool vs_reset_master(const char *new_master);

// Credentials
GList* vs_load_all_credentials(void);
void vs_save_credential(const char *service, const char *username, const char *password);

#endif
