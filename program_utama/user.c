#include "data.h"

//Fungsi untuk melihat alat
void lihat_alat() {
    tampilkan_alat();
}
//Fungsi untuk meminjam alat
void pinjam_alat(const char *username) {
    FILE *fp = fopen("alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *pinjam = fopen("peminjaman.txt", "a");

    if (!fp || !temp || !pinjam) {
        printf("Gagal membuka file!\n");
        return;
    }

    unsigned int id, jumlah;
    Alat alat;
    int found = 0;

    printf("Masukkan ID alat yang ingin dipinjam: ");
    scanf("%u", &id);
    printf("Jumlah yang dipinjam: ");
    scanf("%u", &jumlah);

    while (fscanf(fp, "%u %s %s %s %u %u",
        &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == id && alat.jumlah >= jumlah) {
            alat.jumlah -= jumlah;
            fprintf(pinjam, "%s %u %s %u\n", username, alat.id, alat.nama, jumlah);
            printf("Peminjaman berhasil!\n");
            found = 1;
        }
        fprintf(temp, "%u %s %s %s %u %u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    if (!found) printf("Alat tidak ditemukan atau stok kurang!\n");

    fclose(fp);
    fclose(temp);
    fclose(pinjam);
    remove("alat.txt");
    rename("temp.txt", "alat.txt");
}
//Fungsi untuk melihat alat apa yang sedang dipinjam oleh user
void lihat_pinjaman(const char *username) {
    FILE *fp = fopen("peminjaman.txt", "r");
    if (!fp) {
        printf("Belum ada data peminjaman.\n");
        return;
    }

    Peminjaman p;
    printf("\n=== ALAT YANG DIPINJAM (%s) ===\n", username);
    while (fscanf(fp, "%s %u %s %u", p.username, &p.idAlat, p.namaAlat, &p.jumlahPinjam) == 4) {
        if (strcmp(p.username, username) == 0)
            printf("ID: %u | Nama: %s | Jumlah: %u\n", p.idAlat, p.namaAlat, p.jumlahPinjam);
    }

    fclose(fp);
}
//Fungsi untuk mengembalikan alat
void kembalikan_alat(const char *username) {
    FILE *fp = fopen("peminjaman.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *alatFile = fopen("alat.txt", "r");
    FILE *alatTemp = fopen("alatTemp.txt", "w");

    if (!fp || !temp || !alatFile || !alatTemp) {
        printf("Gagal membuka file!\n");
        return;
    }

    unsigned int id;
    printf("Masukkan ID alat yang dikembalikan: ");
    scanf("%u", &id);

    Peminjaman p;
    Alat alat;
    int found = 0;
    unsigned int jumlahKembali = 0;

    // Hapus dari peminjaman.txt
    while (fscanf(fp, "%s %u %s %u", p.username, &p.idAlat, p.namaAlat, &p.jumlahPinjam) == 4) {
        if (strcmp(p.username, username) == 0 && p.idAlat == id) {
            jumlahKembali = p.jumlahPinjam;
            found = 1;
        } else {
            fprintf(temp, "%s %u %s %u\n", p.username, p.idAlat, p.namaAlat, p.jumlahPinjam);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("peminjaman.txt");
    rename("temp.txt", "peminjaman.txt");

    // Tambahkan kembali stok ke alat.txt
    while (fscanf(alatFile, "%u %s %s %s %u %u", 
        &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == id) {
            alat.jumlah += jumlahKembali;
        }
        fprintf(alatTemp, "%u %s %s %s %u %u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    fclose(alatFile);
    fclose(alatTemp);
    remove("alat.txt");
    rename("alatTemp.txt", "alat.txt");

    if (found)
        printf("Alat berhasil dikembalikan!\n");
    else
        printf("Tidak ada data peminjaman dengan ID tersebut!\n");
}

void menu_user(const char *username) {
    int pilih;
    do {
        printf("\n=== MENU USER (%s) ===\n", username);
        printf("1. Lihat alat tersedia\n");
        printf("2. Pinjam alat\n");
        printf("3. Lihat alat yang dipinjam\n");
        printf("4. Kembalikan alat\n");
        printf("0. Logout\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1: lihat_alat(); break;
            case 2: pinjam_alat(username); break;
            case 3: lihat_pinjaman(username); break;
            case 4: kembalikan_alat(username); break;
            case 0: printf("Logout...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilih != 0);
}
