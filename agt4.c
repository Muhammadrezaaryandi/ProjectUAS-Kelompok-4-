#include "file.h"
/* ---------- LIHAT PEMINJAMAN ----------
   Menampilkan alat yang sedang dipinjam oleh user tertentu.
*/
void lihatPinjaman(char *username) {
    FILE *fp = fopen("data_peminjaman.txt", "r");
    if (!fp) { printf("Belum ada data peminjaman.\n"); return; }

    char user[50], nama[50];
    unsigned int id;
    int found = 0;
    printf("\n=== Peminjaman oleh %s ===\n", username);
    while (fscanf(fp, "%49s %u %49s", user, &id, nama) != EOF) {
        if (strcmp(user, username) == 0) {
            printf("ID: %-3u Nama: %s\n", id, nama);
            found = 1;
        }
    }
    if (!found) printf("Anda belum meminjam alat apapun.\n");
    fclose(fp);
}


void kembalikanAlat(char *username) {
    unsigned int id;
    printf("Masukkan ID alat yang ingin dikembalikan: ");
    if (scanf("%u", &id) != 1) { printf("Input salah.\n"); return; }

    FILE *fp = fopen("data_peminjaman.txt", "r");
    FILE *tmp = fopen("temp_pinjam.txt", "w");
    if (!fp || !tmp) { if (fp) fclose(fp); if (tmp) fclose(tmp); printf("Error file.\n"); return; }

    char user[50], nama[50];
    unsigned int pid;
    int returned = 0;
    while (fscanf(fp, "%49s %u %49s", user, &pid, nama) != EOF) {
        if (strcmp(user, username) == 0 && pid == id) {
            returned = 1; // baris ini dihapus
        } else {
            fprintf(tmp, "%s %u %s\n", user, pid, nama);
        }
    }
    fclose(fp); fclose(tmp);
    remove("data_peminjaman.txt");
    rename("temp_pinjam.txt", "data_peminjaman.txt");

    if (!returned) { printf(" Tidak ditemukan peminjaman dengan ID %u oleh Anda.\n", id); return; }

    // Tambahkan stok alat kembali
    FILE *fa = fopen("data_alat.txt", "r");
    FILE *fatmp = fopen("temp_alat.txt", "w");
    if (!fa || !fatmp) { if (fa) fclose(fa); if (fatmp) fclose(fatmp); printf("Error file.\n"); return; }
Alat a;
    while (fscanf(fa, "%u %49s %49s %49s %u %u", &a.id, a.nama, a.merek, a.model, &a.tahun, &a.jumlah) != EOF) {
        if (a.id == id) a.jumlah++;
        fprintf(fatmp, "%u %s %s %s %u %u\n", a.id, a.nama, a.merek, a.model, a.tahun, a.jumlah);
    }
    fclose(fa); fclose(fatmp);
    remove("data_alat.txt");
    rename("temp_alat.txt", "data_alat.txt");

    printf(" Alat ID %u berhasil dikembalikan.\n",id);
}