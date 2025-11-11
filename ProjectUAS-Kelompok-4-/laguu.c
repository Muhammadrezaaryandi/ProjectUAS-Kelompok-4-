#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD 100
#define MAX_LINE 1000
#define MAX_WORDS 5000

// Ubah semua huruf ke huruf kecil
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Hapus semua karakter kecuali huruf, spasi, dan apostrophe (')
void cleanText(char *str) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i]) || str[i] == ' ' || str[i] == '\'') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

// Cek apakah kata sudah ada di daftar
int isDuplicate(char words[][MAX_WORD], int count, char *word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fin, *fout;
    char line[MAX_LINE];
    char words[MAX_WORDS][MAX_WORD];
    int count = 0;
    char title[200];

    fin = fopen("lirik.txt", "r");
    if (!fin) {
        printf("File lirik.txt tidak ditemukan!\n");
        return 1;
    }

    fout = fopen("kosa-kata.txt", "w");
    if (!fout) {
        printf("Gagal membuat file kosa-kata.txt!\n");
        fclose(fin);
        return 1;
    }

    // Ambil judul (baris pertama)
    fgets(title, sizeof(title), fin);
    fprintf(fout, "%s", title);

    // Baca lirik baris demi baris
    while (fgets(line, sizeof(line), fin)) {
        toLowerCase(line);
        cleanText(line);

        // Ambil kata satu-per-satu
        char *token = strtok(line, " ");
        while (token != NULL) {

            // Lewati token kosong atau hanya apostrophe
            if (strlen(token) > 0 && !(strlen(token) == 1 && token[0] == '\'')) {

                // Masukkan jika belum ada
                if (!isDuplicate(words, count, token)) {
                    strcpy(words[count], token);
                    count++;
                }
            }
            token = strtok(NULL, " ");
        }
    }

    // Tulis kata ke file output
    for (int i = 0; i < count; i++) {
        fprintf(fout, "%s=\n", words[i]);
    }

    fclose(fin);
    fclose(fout);

    printf("Daftar kosa kata berhasil dibuat di file 'kosa-kata.txt'\n");
    return 0;
}