#include "file.h"

// ====================================================
// ANGGOTA 2 - Fungsi LOGIN dan TAMPILKAN ALAT
// ====================================================

/* ---------- LOGIN ----------
   Fungsi login membaca file data_akun.txt dan memeriksa
   apakah username dan password cocok.
   Jika cocok, role disalin ke variabel 'role' dan return 1.
   Jika tidak cocok, return 0.
*/
int login(char *username, char *password, char *role) {
    FILE *fp = fopen("data_akun.txt", "r");
    if (!fp) return 0;

    char u[50], p[50], r[20];
    while (fscanf(fp, "%49s %49s %19s", u, p, r) != EOF) {
        if (strcmp(u, username) == 0 && strcmp(p, password) == 0) {
            strcpy(role, r);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

