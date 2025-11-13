#include "data.h"

//Hanya agar buat tampilan rapi
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

// Menampilkan semua alat
void tampilkan_alat() {
    FILE *fp = fopen("alat.txt", "r");
    if (!fp) {
        printf("Belum ada data alat.\n");
        return;
    }

    Alat alat;
    printf("\n=== DAFTAR ALAT LAB ===\n");

    printf("ID\tNama\t\tMerek\t\tModel\tTahun\tJumlah\n");
    printf("============================================================\n");


    while (fscanf(fp, "%u %s %s %s %u %u", 
        &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        printf("%u\t%-10s\t%-10s\t%-10s\t%u\t%u\n",
               alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    fclose(fp);
}

// Tambah alat baru
void tambah_alat() {
    FILE *fp = fopen("alat.txt", "a");
    if (!fp) {
        printf("Gagal membuka file!\n");
        return;
    }

    Alat alat;
    printf("Masukkan ID alat: "); 
    scanf("%u", &alat.id); 
    getchar();
    printf("Nama alat: "); scanf(" %[^\n]", alat.nama);
    printf("Merek: "); scanf(" %[^\n]", alat.merek);
    printf("Model: "); scanf(" %[^\n]", alat.model);
    printf("Tahun: "); scanf("%u", &alat.tahun);
    printf("Jumlah: "); scanf("%u", &alat.jumlah);

    fprintf(fp, "%u %s %s %s %u %u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    fclose(fp);

    printf("Alat berhasil ditambahkan!\n");
}

// Edit alat
void edit_alat() {
    FILE *fp = fopen("alat.txt", "r");
    if (!fp) {
        printf("Belum ada data alat!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Gagal membuka file sementara!\n");
        fclose(fp);
        return;
    }

    unsigned int target;
    printf("Masukkan ID alat yang ingin diedit: ");
    scanf("%u", &target);

    Alat alat;
    int found = 0;

    while (fscanf(fp, "%u %s %s %s %u %u", 
        &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == target) {
            printf("Masukkan data baru untuk alat %u:\n", target);
            getchar();
            printf("Nama: "); scanf(" %[^\n]", alat.nama);
            printf("Merek: "); scanf(" %[^\n]", alat.merek);
            printf("Model: "); scanf(" %[^\n]", alat.model);
            printf("Tahun: "); scanf("%u", &alat.tahun);
            printf("Jumlah: "); scanf("%u", &alat.jumlah);
            found = 1;
        }
        fprintf(temp, "%u %s %s %s %u %u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    fclose(fp);
    fclose(temp);

    remove("alat.txt");
    rename("temp.txt", "alat.txt");

    if (found) printf("Data alat berhasil diperbarui!\n");
    else printf("ID alat tidak ditemukan!\n");
}

// Hapus alat
void hapus_alat() {
    FILE *fp = fopen("alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Gagal membuka file!\n");
        return;
    }

    unsigned int target;
    printf("Masukkan ID alat yang ingin dihapus: ");
    scanf("%u", &target);

    Alat alat;
    int found = 0;

    while (fscanf(fp, "%u %s %s %s %u %u", 
        &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id != target)
            fprintf(temp, "%u %s %s %s %u %u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("alat.txt");
    rename("temp.txt", "alat.txt");

    if (found) printf("Alat berhasil dihapus!\n");
    else printf("ID tidak ditemukan!\n");
}

// Menu admin
void menu_admin() {
    int pilih;
    do {
        printf("\n=== MENU ADMIN ===\n");
        printf("1. Tampilkan alat\n");
        printf("2. Tambah alat\n");
        printf("3. Edit alat\n");
        printf("4. Hapus alat\n");
        printf("0. Logout\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        switch(pilih) {
            case 1: tampilkan_alat(); break;
            case 2: tambah_alat(); break;
            case 3: edit_alat(); break;
            case 4: hapus_alat(); break;
            case 0: printf("Logout...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilih != 0);
}