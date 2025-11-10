// ====================================================
// ANGGOTA 3 - Fungsi TAMBAH dan EDIT ALAT
// ====================================================

/* ---------- TAMBAH ALAT ----------
   Admin menambahkan data alat baru ke file data_alat.txt.
*/
void tambahAlat() {
    Alat a;
    FILE *fp = fopen("data_alat.txt", "a");
    if (!fp) {
        printf("Gagal membuka data_alat.txt untuk menambah.\n");
        return;
    }

    printf("Masukkan ID Alat: ");
    if (scanf("%u", &a.id) != 1) { printf("Input salah.\n"); return; }
    printf("Masukkan Nama Alat (tanpa spasi): ");
    scanf("%49s", a.nama);
    printf("Masukkan Merek (tanpa spasi): ");
    scanf("%49s", a.merek);
    printf("Masukkan Model (tanpa spasi): ");
    scanf("%49s", a.model);
    printf("Masukkan Tahun Produksi: ");
    scanf("%u", &a.tahun);
    printf("Masukkan Jumlah unit: ");
    scanf("%u", &a.jumlah);

    fprintf(fp, "%u %s %s %s %u %u\n", a.id, a.nama, a.merek, a.model, a.tahun, a.jumlah);
    fclose(fp);
    printf("✅ Alat berhasil ditambahkan.\n");
}

/* ---------- EDIT ALAT ----------
   Admin memilih alat berdasarkan ID, lalu mengubah datanya.
*/
void editAlat() {
    unsigned int id;
    printf("Masukkan ID alat yang akan diedit: ");
    if (scanf("%u", &id) != 1) { printf("Input salah.\n"); return; }

    FILE *fp = fopen("data_alat.txt", "r");
    FILE *tmp = fopen("temp_alat.txt", "w");
    if (!fp || !tmp) { printf("Error file.\n"); if (fp) fclose(fp); if (tmp) fclose(tmp); return; }

    Alat a;
    int found = 0;
    while (fscanf(fp, "%u %49s %49s %49s %u %u", &a.id, a.nama, a.merek, a.model, &a.tahun, &a.jumlah) != EOF) {
        if (a.id == id) {
            found = 1;
            printf("Masukkan Nama baru (tanpa spasi): ");
            scanf("%49s", a.nama);
            printf("Masukkan Merek baru (tanpa spasi): ");
            scanf("%49s", a.merek);
            printf("Masukkan Model baru (tanpa spasi): ");
            scanf("%49s", a.model);
            printf("Masukkan Tahun baru: ");
            scanf("%u", &a.tahun);
            printf("Masukkan Jumlah baru: ");
            scanf("%u", &a.jumlah);
        }
        fprintf(tmp, "%u %s %s %s %u %u\n", a.id, a.nama, a.merek, a.model, a.tahun, a.jumlah);
    }
    fclose(fp); fclose(tmp);
    remove("data_alat.txt");
    rename("temp_alat.txt", "data_alat.txt");
    if (found) printf("✅ Data alat ID %u diperbarui.\n", id);
    else printf("⚠ Alat ID %u tidak ditemukan.\n", id);
}