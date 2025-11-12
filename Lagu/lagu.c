#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD 100
#define MAX_LINE 1000

// Fungsi untuk ubah huruf yang besar jadi kecil semua
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Fungsi untuk hapus tanda baca (sisakan huruf dan spasi)
void removePunctuation(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i]) || str[i] == ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    FILE *fin, *fout;
    char line[MAX_LINE];
    char words[2000][MAX_WORD];
    int count = 0;
    char judul[200] = "";

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

    // Baca baris pertama (judul lagu)
    fgets(line, sizeof(line), fin);
    strcpy(judul, line);
    fprintf(fout, "%s\n", judul);

    // Baca baris berikutnya (lirik)
    while (fgets(line, sizeof(line), fin)) {
        removePunctuation(line);
        toLowerCase(line);

        char *token = strtok(line, " ");
        while (token != NULL) {
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(words[i], token) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found && strlen(token) > 0) {
                strcpy(words[count++], token);
            }
            token = strtok(NULL, " ");
        }
    }

    // Tulis semua kata unik ke file output
    for (int i = 0; i < count; i++) {
        fprintf(fout, "%s=\n", words[i]);
    }

    fclose(fin);
    fclose(fout);

    printf("Daftar kosa kata berhasil dibuat di file 'kosa-kata.txt'\n");
    return 0;
}
