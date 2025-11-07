#include <stdio.h>

int main() {
    char nama[50];

    printf("Masukkan nama kamu: ");
    scanf("%s", nama);  // baca 1 kata (tanpa spasi)

    printf("Halo, %s! Selamat belajar Git & VSCode!\n", nama);

    return 0;
}