#include "alat.h"

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

    int pilihan;

    do {
        if (strcmp(role, "admin") == 0) {
            printf("\n===== MENU ADMIN =====\n");
            printf("1. Lihat data alat\n");
            printf("2. Tambah alat\n");
            printf("3. Edit alat\n");
            printf("4. Hapus alat\n");
            printf("0. Keluar\n");
            garis();
            printf("Pilih menu: ");
            scanf("%d", &pilihan);

            switch (pilihan) {
                case 1: tampilkan_alat(); break;
                case 2: tambah_alat(); break;
                case 3: edit_alat(); break;
                case 4: hapus_alat(); break;
                case 0: printf("Keluar...\n"); break;
                default: printf("[!] Pilihan tidak valid!\n");
            }

        } else if (strcmp(role, "user") == 0) {
            printf("\n===== MENU USER =====\n");
            printf("1. Lihat alat tersedia\n");
            printf("2. Pinjam alat\n");
            printf("3. Lihat alat dipinjam\n");
            printf("4. Kembalikan alat\n");
            printf("0. Keluar\n");
            garis();
            printf("Pilih menu: ");
            scanf("%d", &pilihan);

            switch (pilihan) {
                case 1: tampilkan_alat(); break;
                case 2: pinjam_alat(argv[1]); break;
                case 3: lihat_pinjaman(argv[1]); break;
                case 4: kembalikan_alat(argv[1]); break;
                case 0: printf("Keluar...\n"); break;
                default: printf("[!] Pilihan tidak valid!\n");
            }
        }

    } while (pilihan != 0);

    garis();
    printf("Terima kasih telah menggunakan sistem ini!\n");
    garis();

    return 0;
}