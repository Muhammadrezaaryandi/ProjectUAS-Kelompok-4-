#include "file.h"
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }

    char role[20];
    if (!login(argv[1], argv[2], role)) {
        printf("Login gagal: username/password salah.\n");
        return 1;
    }
    printf("Selamat datang %s (role: %s)\n", argv[1], role);

    int pilihan = 0;
    do {
        if (strcmp(role, "admin") == 0) {
            printf("\n=== MENU ADMIN ===\n");
            printf("1. Lihat alat\n2. Tambah alat\n3. Hapus alat\n4. Edit alat\n5. Keluar\nPilih: ");
            if (scanf("%d", &pilihan) != 1) break;
            switch (pilihan) {
                case 1: tampilkanAlat(); break;
                case 2: tambahAlat(); break;
                case 3: hapusAlat(); break;
                case 4: editAlat(); break;
                case 5: printf("Keluar...\n"); break;
                default: printf("Pilihan tidak valid.\n");
            }
        } else {
            printf("\n=== MENU USER ===\n");
            printf("1. Lihat alat\n2. Pinjam alat\n3. Lihat pinjaman\n4. Kembalikan alat\n5. Keluar\nPilih: ");
            if (scanf("%d", &pilihan) != 1) break;
            switch (pilihan) {
                case 1: tampilkanAlat(); break;
                case 2: pinjamAlat(argv[1]); break;
                case 3: lihatPinjaman(argv[1]); break;
                case 4: kembalikanAlat(argv[1]); break;
                case 5: printf("Keluar...\n"); break;
                default: printf("Pilihan tidak valid.\n");
            }
        }
    } while (pilihan != 5);

return 0;
}