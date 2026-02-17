#ifndef CREDENTIAL_H
#define CREDENTIAL_H

#define MAX_LEN 128

typedef struct {
    char service[MAX_LEN];
    char username[MAX_LEN];
    char password[MAX_LEN];
} Credential;

#endif
