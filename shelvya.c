#include "file.h"
#include <stdio.h>


/* ---------- HAPUS ALAT ----------
   Admin menghapus alat dari daftar berdasarkan ID.
*/
void hapusAlat() {
    unsigned int id;
    printf("Masukkan ID alat yang akan dihapus: ");
    if (scanf("%u", &id) != 1) { printf("Input salah.\n"); return; }

    FILE *fp = fopen("data_alat.txt", "r");
    FILE *tmp = fopen("temp_alat.txt", "w");
    if (!fp || !tmp) { printf("Error file.\n"); if (fp) fclose(fp); if (tmp) fclose(tmp); return; }

    Alat a;
    int found = 0;
    while (fscanf(fp, "%u %49s %49s %49s %u %u", &a.id, a.nama, a.merek, a.model, &a.tahun, &a.jumlah) != EOF) {
        if (a.id == id) { found = 1; continue; } // skip baris yang dihapus
        fprintf(tmp, "%u %s %s %s %u %u\n", a.id, a.nama, a.merek, a.model, a.tahun, a.jumlah);
    }
    fclose(fp); fclose(tmp);
    remove("data_alat.txt");
    rename("temp_alat.txt", "data_alat.txt");
    if (found) printf("Alat ID %u dihapus.\n", id);
    else printf("⚠ Alat ID %u tidak ditemukan.\n", id);
}

/* ---------- PINJAM ALAT ----------
   User meminjam alat. Stok alat dikurangi 1 dan data dicatat di data_peminjaman.txt.
*/
void pinjamAlat(char *username) {
    unsigned int id;
    printf("Masukkan ID alat yang ingin dipinjam: ");
    if (scanf("%u", &id) != 1) { printf("Input salah.\n"); return; }

    FILE *fp = fopen("data_alat.txt", "r");
    FILE *tmp = fopen("temp_alat.txt", "w");
    FILE *pinjam = fopen("data_peminjaman.txt", "a");
    if (!fp || !tmp || !pinjam) { printf("Error file.\n"); if (fp) fclose(fp); if (tmp) fclose(tmp); if (pinjam) fclose(pinjam); return; }

    Alat a;
    int found = 0;
    while (fscanf(fp, "%u %49s %49s %49s %u %u", &a.id, a.nama, a.merek, a.model, &a.tahun, &a.jumlah) != EOF) {
        if (a.id == id) {
            if (a.jumlah > 0) {
                a.jumlah--;
                fprintf(pinjam, "%s %u %s\n", username, a.id, a.nama);
                printf("Anda meminjam: %s (ID %u)\n", a.nama, a.id);
                found = 1;
            } else {
                printf("⚠ Stok alat habis.\n");
            }
        }
        fprintf(tmp, "%u %s %s %s %u %u\n", a.id, a.nama, a.merek, a.model, a.tahun, a.jumlah);
    }

    fclose(fp); fclose(tmp); fclose(pinjam);
    remove("data_alat.txt");
    rename("temp_alat.txt", "data_alat.txt");

    if (!found) printf("⚠ Alat ID %u tidak ditemukan atau stok habis.\n", id);
}