#include "vault_storage.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

// ----- Master Password Handling -----
bool vs_master_exists(void) {
    FILE *f = fopen(MASTER_FILE, "r");
    if (!f) return false;
    fclose(f);
    return true;
}

bool vs_save_master(const char *master, const char *recovery) {
    FILE *f = fopen(MASTER_FILE, "w");
    if (!f) return false;
    fprintf(f, "%s\n%s\n", master, recovery);
    fclose(f);
    return true;
}

bool vs_verify_master(const char *master) {
    FILE *f = fopen(MASTER_FILE, "r");
    if (!f) return false;
    char saved[MAX_LEN], recovery[MAX_LEN];
    fgets(saved, sizeof(saved), f);
    fgets(recovery, sizeof(recovery), f);
    saved[strcspn(saved, "\n")] = 0;
    fclose(f);
    return strcmp(master, saved) == 0;
}

bool vs_check_recovery(const char *answer) {
    FILE *f = fopen(MASTER_FILE, "r");
    if (!f) return false;
    char saved[MAX_LEN], recovery[MAX_LEN];
    fgets(saved, sizeof(saved), f);
    fgets(recovery, sizeof(recovery), f);
    recovery[strcspn(recovery, "\n")] = 0;
    fclose(f);
    return strcmp(answer, recovery) == 0;
}

bool vs_reset_master(const char *new_master) {
    FILE *f = fopen(MASTER_FILE, "r+");
    if (!f) return false;
    char old[MAX_LEN], recovery[MAX_LEN];
    fgets(old, sizeof(old), f);
    fgets(recovery, sizeof(recovery), f);

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%s\n%s\n", new_master, recovery);
    fclose(f);
    return true;
}

// ----- Credentials Handling -----
GList* vs_load_all_credentials(void) {
    GList *list = NULL;
    FILE *f = fopen(CREDENTIAL_FILE, "r");
    if (!f) return list;

    Credential *c = NULL;
    char service[MAX_LEN], username[MAX_LEN], password[MAX_LEN];
    while (fscanf(f, "%127s %127s %127s\n", service, username, password) == 3) {
        c = malloc(sizeof(Credential));
        strncpy(c->service, service, MAX_LEN);
        strncpy(c->username, username, MAX_LEN);
        strncpy(c->password, password, MAX_LEN);
        list = g_list_append(list, c);
    }
    fclose(f);
    return list;
}

void vs_save_credential(const char *service, const char *username, const char *password) {
    FILE *f = fopen(CREDENTIAL_FILE, "a");
    if (!f) return;
    fprintf(f, "%s %s %s\n", service, username, password);
    fclose(f);
}
