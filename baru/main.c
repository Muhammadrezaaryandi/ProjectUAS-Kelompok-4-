#include <stdio.h>
#include <string.h> 
#include "alat.h"

void garis() {
    printf("========================================================================\n");
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Format: %s <username> <password>\n", argv[0]);
        return 1;
    }

    char role[10];
    if (!login(argv[1], argv[2], role)) {
        printf("[!] Login gagal. Username atau password salah.\n");
        return 0;
    }

   
    printf("\n");
    garis();
    printf(" SELAMAT DATANG, %s (%s)\n", argv[1], role);
    garis();

    if (strcmp(role, "admin") == 0) {
        menu_admin(); 
    } else if (strcmp(role, "user") == 0) {
        menu_user(argv[1]); 
    }
    garis();
    printf("Terima kasih telah menggunakan sistem ini!\n");
    garis();

    return 0;
}