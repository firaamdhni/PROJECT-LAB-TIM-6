#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Definisi variabel global
Alat_Lab alat_lab[MAX_ALAT];
unsigned int total_alat = 0;
Peminjaman peminjaman[MAX_PINJAMAN];
unsigned int total_peminjaman = 0;


// Fungsi membaca data dari file
void data() {
    FILE *file = fopen("alat_lab.txt", "r");
    if (file == NULL) {
        printf("File alat_lab.txt tidak ditemukan. Membuat file baru...\n");
        file = fopen("alat_lab.txt", "w");
        if (file == NULL) {
            printf("Gagal membuat file alat_lab.txt.\n");
            exit(1);
        }
        fclose(file);
        return;
    }
