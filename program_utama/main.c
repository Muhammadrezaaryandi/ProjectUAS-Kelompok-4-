#include <stdio.h>
#include <string.h> // Diperlukan untuk strcmp
#include "data.h"

// Fungsi ini boleh tetap ada di main.c
void garis() {
    printf("=============================================\n");
}

int main(int argc, char *argv[]) {
    // 1. Pengecekan argumen (Sudah benar)
    if (argc < 3) {
        printf("Format: %s <username> <password>\n", argv[0]);
        return 1;
    }

    // 2. Proses Login (Sudah benar)
    char role[10];
    if (!login(argv[1], argv[2], role)) {
        printf("[!] Login gagal. Username atau password salah.\n");
        return 0;
    }

    // 3. Pesan Selamat Datang (Sudah benar)
    printf("\n");
    garis();
    printf(" SELAMAT DATANG, %s (%s)\n", argv[1], role);
    garis();

    // 4. MEMPERBAIKI LOGIKA MENU
    // Hapus seluruh blok 'do-while' yang Anda miliki sebelumnya.
    // Ganti dengan logika if-else sederhana untuk mendelegasikan
    // ke fungsi menu yang sesuai.
    
    if (strcmp(role, "admin") == 0) {
        // Panggil fungsi menu admin dari admin.c
        // Fungsi ini memiliki loop do-while-nya sendiri
        menu_admin(); 
    } else if (strcmp(role, "user") == 0) {
        // Panggil fungsi menu user dari user.c
        // Fungsi ini memiliki loop do-while-nya sendiri
        menu_user(argv[1]); 
    }

    // 5. Pesan Penutup
    // Kode ini akan dieksekusi SETELAH pengguna memilih '0' (Logout)
    // dari menu_admin() atau menu_user(), karena loop-nya sudah selesai.
    garis();
    printf("Terima kasih telah menggunakan sistem ini!\n");
    garis();

    return 0;
}