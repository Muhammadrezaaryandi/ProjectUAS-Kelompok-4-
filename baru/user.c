#include "data.h"

// Fungsi untuk menampilkan seluruh alat yang tersedia
void lihat_alat() {
    // Memanggil fungsi tampilkan_alat() dari file alat.h
    tampilkan_alat();
}

// Fungsi untuk melakukan peminjaman alat
void pinjam_alat(const char *username) {
    // Membuka file data alat, file sementara, dan file untuk mencatat peminjaman
    FILE *fp = fopen("alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *pinjam = fopen("peminjaman.txt", "a");

    // Mengecek apakah semua file berhasil dibuka
    if (!fp || !temp || !pinjam) {
        printf("Tidak dapat membuka file!\n");
        return;
    }

    // Mendeklarasikan variabel untuk menyimpan id alat dan jumlah alat
    unsigned int id, jumlah;
    Alat alat;
    // Variabel found akan digunakan untuk mengecek apakah ID alat ditemukan atau tidak
    int found = 0;

    // Meminta input ID alat dan jumlah alat yang ingin dipinjam oleh user
    printf("Masukkan ID alat: ");
    scanf("%u", &id);
    printf("Jumlah yang dipinjam: ");
    scanf("%u", &jumlah);

    // Membaca isi file alat baris per baris
    while (fscanf(fp, "%u,%[^,],%[^,],%[^,],%u,%u\n",
        &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        
        // Mengecek apakah ID cocok dan stok mencukupi, maka lakukan peminjaman dan mengurangi stok di file alat.txt
        if (alat.id == id && alat.jumlah >= jumlah) 
        {
            alat.jumlah -= jumlah;

            // Catat transaksi ke file peminjaman.txt
            fprintf(pinjam, "%s %u %s %u\n", username, alat.id, alat.nama, jumlah);
            printf("Peminjaman berhasil!\n");
            // Menandai bahwa alat ditemukan dan proses berhasil
            found = 1;
        }
        // Menulis data alat yang sudah diperbarui ataupun tidak ke file sementara
        fprintf(temp, "%u,%s,%s,%s,%u,%u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    if (!found) {
        printf("Alat tidak ditemukan atau stok kurang!\n");
    }

    // Menutup file dan mengganti file lama dengan file baru
    fclose(fp);
    fclose(temp);
    fclose(pinjam);
    remove("alat.txt");
    rename("temp.txt", "alat.txt");
}

// Fungsi untuk menampilkan alat yang sedang dipinjam oleh user
void lihat_pinjaman(const char *username) {
    // Membuka file peminjaman.txt untuk dibaca
    FILE *fp = fopen("peminjaman.txt", "r");
    if (!fp) {
        printf("Belum ada data peminjaman.\n");
        return;
    }

    Peminjaman p;
    printf("\n=== ALAT YANG DIPINJAM (%s) ===\n", username);

    // Membaca riwayat peminjaman baris demi baris
    while (fscanf(fp, "%s %u %s %u", p.username, &p.idAlat, p.namaAlat, &p.jumlahPinjam) == 4) {
        // Menampilkan data yang hanya dimiliki user yang sama
        if (strcmp(p.username, username) == 0)
            printf("ID: %u | Nama: %s | Jumlah: %u\n", p.idAlat, p.namaAlat, p.jumlahPinjam);
    }

    fclose(fp);
}

// Fungsi untuk mengembalikan alat yang sebelumnya dipinjam oleh user
void kembalikan_alat(const char *username) {
    // Membuka file peminjaman, file sementara, file alat, dan file alat sementara
    FILE *fp = fopen("peminjaman.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *alatFile = fopen("alat.txt", "r");
    FILE *alatTemp = fopen("alatTemp.txt", "w");

    // Mengecek apakah semua file berhasil dibuka
    if (!fp || !temp || !alatFile || !alatTemp) {
        printf("Gagal membuka file!\n");
        return;
    }

    unsigned int id;
    // Meminta user untuk menginput ID alat yang ingin dikembalikan
    printf("Masukkan ID alat: ");
    scanf("%u", &id);

    // Struct untuk menyimpan data peminjaman dan data alat
    Peminjaman p;
    Alat alat;
    
    int found = 0;
    unsigned int jumlahKembali = 0;

    // Menghapus data peminjaman sesuai ID alat yang dipinjam
    while (fscanf(fp, "%s %u %s %u", p.username, &p.idAlat, p.namaAlat, &p.jumlahPinjam) == 4) {
        // Mengecek apakah data milik user dan ID alat cocok, maka ambil jumlah yang dikembalikan
        if (strcmp(p.username, username) == 0 && p.idAlat == id) {
            jumlahKembali = p.jumlahPinjam;
            found = 1;
        } else {
            fprintf(temp, "%s %u %s %u\n", p.username, p.idAlat, p.namaAlat, p.jumlahPinjam);
        }
    }

    // Menutup file dan mengganti file lama dengan file baru
    fclose(fp);
    fclose(temp);
    remove("peminjaman.txt");
    rename("temp.txt", "peminjaman.txt");

    // Menambah stok kembali ke file alat.txt
    while (fscanf(alatFile, "%u,%[^,],%[^,],%[^,],%u,%u\n", 
        &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == id) {
            alat.jumlah += jumlahKembali;
        }
        fprintf(alatTemp, "%u,%s,%s,%s,%u,%u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    // Menutup file dan mengganti file lama dengan file baru
    fclose(alatFile);
    fclose(alatTemp);
    remove("alat.txt");
    rename("alatTemp.txt", "alat.txt");

    // Mengecek apakah alat ditemukan
    if (found)
        printf("Alat telah dikembalikan!\n");
    else
        printf("Tidak ada data peminjaman dengan ID tersebut!\n");
}

// Menu utama untuk user
void menu_user(const char *username) {
    int pilih;
    int status_baca; 

    do {
        // Menampilkan daftar menu
        printf("\n=== MENU USER (%s) ===\n", username);
        printf("1. Lihat alat tersedia\n");
        printf("2. Pinjam alat\n");
        printf("3. Lihat alat yang dipinjam\n");
        printf("4. Kembalikan alat\n");
        printf("0. Logout\n");
        printf("Pilih: ");

        // Memastikan user memasukkan angka
        status_baca = scanf("%d", &pilih);

        // Jika input valid maka menu akan dilanjutkan
        if (status_baca == 1) {
            switch (pilih) {
                case 1: lihat_alat(); break;
                case 2: pinjam_alat(username); break;
                case 3: lihat_pinjaman(username); break;
                case 4: kembalikan_alat(username); break;
                case 0: printf("Logout...\n"); break;
                default: printf("Pilihan tidak valid!\n");
            }
        } else {
            // Jika input berupa huruf, maka input tidak valid
            printf("Harap masukkan angka!\n");
            // Membersihkan buffer
            while (getchar() != '\n');
            pilih = -1;
        }
    } while (pilih != 0);
}