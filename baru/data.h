#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =============================
// STRUCT DATA
// =============================
typedef struct {
    unsigned int id;
    char nama[50];
    char merek[50];
    char model[50];
    unsigned int tahun;
    unsigned int jumlah;
} Alat;

typedef struct {
    char username[50];
    char password[50];
    char role[10]; // "admin" atau "user"
} Akun;

typedef struct {
    char username[50];
    unsigned int idAlat;
    char namaAlat[50];
    unsigned int jumlahPinjam;
} Peminjaman;

// DEKLARASI FUNGSI
void garis(void);
// login.c
int login(const char *username, const char *password, char *role);

// admin.c
void menu_admin();
void tambah_alat();
void tampilkan_alat();
void edit_alat();
void hapus_alat();

// user.c
void menu_user(const char *username);
void lihat_alat();
void pinjam_alat(const char *username);
void lihat_pinjaman(const char *username);
void kembalikan_alat(const char *username);
#endif