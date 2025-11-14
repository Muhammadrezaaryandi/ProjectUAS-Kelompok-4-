#include "data.h"

// Bagian ini digunakan untuk membaca sebuah file teks
// dan mengembalikan jumlah baris yang ada di dalam file tersebut.
int hitung_baris_file(char *namaFile) 
{
    FILE *fp = fopen(namaFile, "r");
    if (!fp) return 0;
    int count = 0;
    char buffer[255];
    while (fgets(buffer, sizeof(buffer), fp)) count++;
    fclose(fp);
    return count;
}

// Bagian ini berfungsi untuk membaca semua data alat dari file "alat.txt"
void tampilkan_alat()
{
    FILE *fp = fopen("alat.txt", "r");
    if (!fp)
    {
        printf("Belum ada data alat.\n");
        return;
    }

    Alat alat;
    printf("\n=== DAFTAR ALAT LAB ===\n");
    printf("%-5s %-20s %-15s %-15s %-7s %s\n", 
           "ID", "Nama", "Merek", "Model", "Tahun", "Jumlah");
    printf("========================================================================\n");

    while (fscanf(fp, "%u,%[^,],%[^,],%[^,],%u,%u\n", 
        &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6)
        {
        
        printf("%-5u %-20s %-15s %-15s %-7u %u\n",
               alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
        }

    fclose(fp);
}
// Bagian ini berfungsi untuk menambahkan data alat baru ke dalam file "alat.txt"
void tambah_alat()
{
    FILE *fp = fopen("alat.txt", "a");
    if (!fp) 
    {
        printf("Tidak dapat membuka file!\n");
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

    fprintf(fp, "%u,%s,%s,%s,%u,%u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    fclose(fp);

    printf("Alat yang baru berhasil ditambahkan!\n");
}
// Bagian ini berfungsi untuk mengedit data alat yang diliat dari ID
// dan membuat file sementara (temp.txt) untuk menyimpan hasil edit, dan mengganti file lama dengan file baru
void edit_alat() 
{
    FILE *fp = fopen("alat.txt", "r");
    if (!fp) 
    {
        printf("Belum ada data alat!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) 
    {
        printf("Tidak dapat membuka file sementara!\n");
        fclose(fp);
        return;
    }

    unsigned int target;
    printf("Masukkan ID alat: ");
    scanf("%u", &target);

    Alat alat;
    int found = 0;
    
   while (fscanf(fp, "%u,%[^,],%[^,],%[^,],%u,%u\n", 
    &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) 
    { 
        if (alat.id == target) 
        {
            printf("Masukkan data untuk alat baru %u:\n", target);
            getchar();
            printf("Nama: "); scanf(" %[^\n]", alat.nama);
            printf("Merek: "); scanf(" %[^\n]", alat.merek);
            printf("Model: "); scanf(" %[^\n]", alat.model);
            printf("Tahun: "); scanf("%u", &alat.tahun);
            printf("Jumlah: "); scanf("%u", &alat.jumlah);
            found = 1;
        }
        fprintf(temp, "%u,%s,%s,%s,%u,%u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    fclose(fp);
    fclose(temp);

    remove("alat.txt");
    rename("temp.txt", "alat.txt");

    if (found) printf("Data alat berhasil diperbarui!\n");
    else printf("ID alat tidak ditemukan!\n");
}
// Bagian ini berfungsi untuk menghapus data alat dari file "alat.txt" berdasarkan ID alat
// Yang tidak kehapus disalin ke temp.txt, file lama dihapus, dan temp.txt diganti jadi "alat.txt"
void hapus_alat() {
    FILE *fp = fopen("alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) 
    {
        printf("Tidak dapat membuka file!\n");
        return;
    }

    unsigned int target;
    printf("Masukkan ID alat: ");
    scanf("%u", &target);

    Alat alat;
    int found = 0;

    while 
    (fscanf(fp, "%u,%[^,],%[^,],%[^,],%u,%u\n",
    &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id != target)
        fprintf(temp, "%u,%s,%s,%s,%u,%u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
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

// Bagian ini menampilkan daftar menu utama untuk admin
void menu_admin() 
{
    int pilih = -1;
    int status_baca; 

    do {
        printf("\n=== MENU ADMIN ===\n");
        printf("1. Tampilkan alat\n");
        printf("2. Tambah alat\n");
        printf("3. Edit alat\n");
        printf("4. Hapus alat\n");
        printf("0. Logout\n");
        printf("Pilih: ");

        status_baca = scanf("%d", &pilih);

        if (status_baca == 1) 
        {
            switch(pilih) {
                case 1: tampilkan_alat(); break;
                case 2: tambah_alat(); break;
                case 3: edit_alat(); break;
                case 4: hapus_alat(); break;
                case 0: printf("Logout...\n"); break;
                default: printf("Pilihan tidak valid!\n");
            }
        } else {
            printf("Harap masukkan angka!\n");
            while (getchar() != '\n');
        }
    } while (pilih != 0); 
}