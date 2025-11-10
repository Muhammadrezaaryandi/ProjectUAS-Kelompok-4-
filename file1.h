#ifndef file.h
#define file.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data alat laboratorium
typedef struct {
    unsigned int id;
    char nama[50];
    char merek[50];
    char model[50];
    unsigned int tahun;
    unsigned int jumlah;
} Alat;

// Deklarasi fungsi
int login(char *username, char *password, char *role);
void tampilkanAlat();
void tambahAlat();
void hapusAlat();
void editAlat();
void pinjamAlat(char *username);
void lihatPinjaman(char *username);
void kembalikanAlat(char *username);

#endif