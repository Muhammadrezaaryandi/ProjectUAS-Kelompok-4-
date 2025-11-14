#include "data.h"

int login(const char *username, const char *password, char *role)
{
    FILE *fp = fopen("data_akun.txt", "r");
    if (!fp) {
        printf("File akun.txt tidak ditemukan!\n");
        return 0;
    }

    Akun akun;
    while (fscanf(fp, "%s %s %s", akun.username, akun.password, akun.role) == 3) {
        if (strcmp(username, akun.username) == 0 && strcmp(password, akun.password) == 0) {
            strcpy(role, akun.role);
            fclose(fp);
            return 1; // login berhasil
        }
    }

    fclose(fp);

    return 0; // gagal login
}