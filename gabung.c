#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ====================================================
//  SISTEM PEMINJAMAN ALAT LABORATORIUM
//  Versi Lengkap dan Terstruktur (Admin & User)
// ====================================================

// ---------------------- STRUKTUR DATA ----------------------

typedef struct {
    unsigned int id;         // ID alat
    char nama[50];           // Nama alat
    char merek[50];          // Merek alat
    char model[50];          // Model alat
    unsigned int tahun;      // Tahun produksi
    unsigned int jumlah;     // Jumlah stok tersedia
} Alat;

typedef struct {
    char username[30];
    char password[30];
    char role[10]; // admin / user
} Akun;

// ---------------------- DEKLARASI FUNGSI ----------------------

int login(char *username, char *password, char *role);
void tampilkan_alat();
void tambah_alat();
void edit_alat();
void hapus_alat();
void pinjam_alat(char *username);
void lihat_pinjaman(char *username);
void kembalikan_alat(char *username);
int hitung_baris_file(char *namaFile);
void garis();

// ====================================================
//                    FUNGSI LOGIN
// ====================================================

int login(char *username, char *password, char *role) {
    FILE *fp = fopen("data_akun.txt", "r");
    if (!fp) {
        printf("[!] Gagal membuka file akun.\n");
        return 0;
    }

    Akun akun;
    while (fscanf(fp, "%s %s %s", akun.username, akun.password, akun.role) == 3) {
        if (strcmp(akun.username, username) == 0 && strcmp(akun.password, password) == 0) {
            strcpy(role, akun.role);
            fclose(fp);
            return 1; // sukses
        }
    }

    fclose(fp);
    return 0; // gagal
}

// ====================================================
//        FUNGSI TAMBAHAN (UNTUK TAMPILAN RAPI)
// ====================================================

void garis() {
    printf("============================================================\n");
}

int hitung_baris_file(char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    if (!fp) return 0;
    int count = 0;
    char buffer[255];
    while (fgets(buffer, sizeof(buffer), fp)) count++;
    fclose(fp);
    return count;
}

// ====================================================
//              FUNGSI LIHAT DATA ALAT
// ====================================================

void tampilkan_alat() {
    FILE *fp = fopen("data_alat.txt", "r");
    if (!fp) {
        printf("[!] File data_alat.txt tidak ditemukan!\n");
        return;
    }

    Alat alat;
    garis();
    printf(" DAFTAR ALAT LABORATORIUM\n");
    garis();
    printf("%-5s %-15s %-10s %-10s %-5s %-5s\n", "ID", "Nama", "Merek", "Model", "Thn", "Jml");
    garis();

    int count = 0;
    while (fscanf(fp, "%u %s %s %s %u %u", 
                  &alat.id, alat.nama, alat.merek, alat.model, 
                  &alat.tahun, &alat.jumlah) == 6) {
        printf("%-5u %-15s %-10s %-10s %-5u %-5u\n", 
               alat.id, alat.nama, alat.merek, alat.model, 
               alat.tahun, alat.jumlah);
        count++;
    }

    if (count == 0)
        printf("[!] Tidak ada data alat yang tersimpan.\n");

    garis();
    fclose(fp);
}

// ====================================================
//           FUNGSI TAMBAH DATA ALAT (ADMIN)
// ====================================================

void tambah_alat() {
    FILE *fp = fopen("data_alat.txt", "a");
    if (!fp) {
        printf("[!] Gagal membuka file data_alat.txt\n");
        return;
    }

    Alat alat;
    printf("Masukkan ID alat        : "); scanf("%u", &alat.id);
    printf("Masukkan Nama alat      : "); scanf("%s", alat.nama);
    printf("Masukkan Merek alat     : "); scanf("%s", alat.merek);
    printf("Masukkan Model alat     : "); scanf("%s", alat.model);
    printf("Masukkan Tahun produksi : "); scanf("%u", &alat.tahun);
    printf("Masukkan Jumlah unit    : "); scanf("%u", &alat.jumlah);

    fprintf(fp, "%u %s %s %s %u %u\n", 
            alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);

    fclose(fp);
    printf("[+] Alat berhasil ditambahkan!\n");
}

// ====================================================
//           FUNGSI EDIT DATA ALAT (ADMIN)
// ====================================================

void edit_alat() {
    FILE *fp = fopen("data_alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("[!] Gagal membuka file!\n");
        return;
    }

    unsigned int id;
    int found = 0;
    printf("Masukkan ID alat yang ingin diedit: ");
    scanf("%u", &id);

    Alat alat;
    while (fscanf(fp, "%u %s %s %s %u %u", 
                  &alat.id, alat.nama, alat.merek, alat.model, 
                  &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == id) {
            found = 1;
            printf("Masukkan Nama baru   : "); scanf("%s", alat.nama);
            printf("Masukkan Merek baru  : "); scanf("%s", alat.merek);
            printf("Masukkan Model baru  : "); scanf("%s", alat.model);
            printf("Masukkan Tahun baru  : "); scanf("%u", &alat.tahun);
            printf("Masukkan Jumlah baru : "); scanf("%u", &alat.jumlah);
        }
        fprintf(temp, "%u %s %s %s %u %u\n", 
                alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    fclose(fp);
    fclose(temp);
    remove("data_alat.txt");
    rename("temp.txt", "data_alat.txt");

    if (found)
        printf("[✓] Data alat berhasil diedit!\n");
    else
        printf("[!] ID tidak ditemukan.\n");
}

// ====================================================
//           FUNGSI HAPUS DATA ALAT (ADMIN)
// ====================================================

void hapus_alat() {
    FILE *fp = fopen("data_alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("[!] Gagal membuka file.\n");
        return;
    }

    unsigned int id;
    int found = 0;
    printf("Masukkan ID alat yang ingin dihapus: ");
    scanf("%u", &id);

    Alat alat;
    while (fscanf(fp, "%u %s %s %s %u %u", 
                  &alat.id, alat.nama, alat.merek, alat.model, 
                  &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id != id) {
            fprintf(temp, "%u %s %s %s %u %u\n", 
                    alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("data_alat.txt");
    rename("temp.txt", "data_alat.txt");

    if (found)
        printf("[✓] Data alat berhasil dihapus!\n");
    else
        printf("[!] ID tidak ditemukan.\n");
}

// ====================================================
//           FUNGSI PINJAM ALAT (USER)
// ====================================================

void pinjam_alat(char *username) {
    tampilkan_alat();

    FILE *fp = fopen("data_alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *peminjaman = fopen("data_peminjaman.txt", "a");

    if (!fp || !temp || !peminjaman) {
        printf("[!] Gagal membuka file.\n");
        return;
    }

    unsigned int id, jumlah_pinjam;
    printf("Masukkan ID alat yang ingin dipinjam: ");
    scanf("%u", &id);
    printf("Masukkan jumlah yang dipinjam: ");
    scanf("%u", &jumlah_pinjam);

    Alat alat;
    int found = 0;

    while (fscanf(fp, "%u %s %s %s %u %u", 
                  &alat.id, alat.nama, alat.merek, alat.model, 
                  &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == id) {
            if (alat.jumlah >= jumlah_pinjam) {
                alat.jumlah -= jumlah_pinjam;
                fprintf(peminjaman, "%s %u %s %u\n", username, alat.id, alat.nama, jumlah_pinjam);
                found = 1;
                printf("[✓] Peminjaman berhasil!\n");
            } else {
                printf("[!] Stok tidak cukup!\n");
                found = 1;
            }
        }
        fprintf(temp, "%u %s %s %s %u %u\n", 
                alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    fclose(fp);
    fclose(temp);
    fclose(peminjaman);
    remove("data_alat.txt");
    rename("temp.txt", "data_alat.txt");

    if (!found)
        printf("[!] ID alat tidak ditemukan.\n");
}

// ====================================================
//          FUNGSI LIHAT PINJAMAN (USER)
// ====================================================

void lihat_pinjaman(char *username) {
    FILE *fp = fopen("data_peminjaman.txt", "r");
    if (!fp) {
        printf("[!] Belum ada data peminjaman.\n");
        return;
    }

    char user[30], nama[50];
    unsigned int id, jumlah;
    int found = 0;

    garis();
    printf(" DAFTAR PEMINJAMAN (%s)\n", username);
    garis();
    printf("%-10s %-5s %-15s %-5s\n", "User", "ID", "Nama", "Jml");
    garis();

    while (fscanf(fp, "%s %u %s %u", user, &id, nama, &jumlah) == 4) {
        if (strcmp(user, username) == 0) {
            printf("%-10s %-5u %-15s %-5u\n", user, id, nama, jumlah);
            found = 1;
        }
    }

    if (!found)
        printf("[!] Kamu belum meminjam alat apa pun.\n");

    garis();
    fclose(fp);
}

// ====================================================
//           FUNGSI KEMBALIKAN ALAT (USER)
// ====================================================

void kembalikan_alat(char *username) {
    lihat_pinjaman(username);

    FILE *fp = fopen("data_peminjaman.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *alatfile = fopen("data_alat.txt", "r");
    FILE *alattemp = fopen("alat_temp.txt", "w");

    if (!fp || !temp || !alatfile || !alattemp) {
        printf("[!] Gagal membuka file.\n");
        return;
    }

    unsigned int id, jumlah_kembali;
    printf("Masukkan ID alat yang ingin dikembalikan: ");
    scanf("%u", &id);
    printf("Masukkan jumlah yang dikembalikan: ");
    scanf("%u", &jumlah_kembali);

    char user[30], nama[50];
    unsigned int alat_id, jumlah;
    int found = 0;

    // Update data peminjaman
    while (fscanf(fp, "%s %u %s %u", user, &alat_id, nama, &jumlah) == 4) {
        if (strcmp(user, username) == 0 && alat_id == id && jumlah >= jumlah_kembali) {
            jumlah -= jumlah_kembali;
            found = 1;
            if (jumlah > 0)
                fprintf(temp, "%s %u %s %u\n", user, alat_id, nama, jumlah);
        } else {
            fprintf(temp, "%s %u %s %u\n", user, alat_id, nama, jumlah);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("data_peminjaman.txt");
    rename("temp.txt", "data_peminjaman.txt");

    // Update stok alat
    Alat alat;
    while (fscanf(alatfile, "%u %s %s %s %u %u", 
                  &alat.id, alat.nama, alat.merek, alat.model, 
                  &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == id) alat.jumlah += jumlah_kembali;
        fprintf(alattemp, "%u %s %s %s %u %u\n", 
                alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    fclose(alatfile);
    fclose(alattemp);
    remove("data_alat.txt");
    rename("alat_temp.txt", "data_alat.txt");

    if (found)
        printf("[✓] Pengembalian berhasil!\n");
    else
        printf("[!] Data peminjaman tidak ditemukan.\n");
}

// ====================================================
//                      MAIN PROGRAM
// ====================================================

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