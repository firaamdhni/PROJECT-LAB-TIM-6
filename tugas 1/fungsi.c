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
    
while (fscanf(file, "%u %49s %49s %49s %u %u %u",
                  &alat_lab[total_alat].Id_Alat,
                  alat_lab[total_alat].Nama_Alat,
                  alat_lab[total_alat].Merek,
                  alat_lab[total_alat].Model,
                  &alat_lab[total_alat].Tahun_Produksi,
                  &alat_lab[total_alat].Jumlah_Unit,
                  &alat_lab[total_alat].Jumlah_Tersedia) != EOF) {
        total_alat++;
    }
    fclose(file);
}

// Fungsi menyimpan data ke file
void simpan_data() {
    FILE *file = fopen("alat_lab.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file alat_lab.txt untuk menyimpan data.\n");
        return;
    }

    for (unsigned int i = 0; i < total_alat; i++) {
        fprintf(file, "%u %s %s %s %u %u %u\n",
                alat_lab[i].Id_Alat,
                alat_lab[i].Nama_Alat,
                alat_lab[i].Merek,
                alat_lab[i].Model,
                alat_lab[i].Tahun_Produksi,
                alat_lab[i].Jumlah_Unit,
                alat_lab[i].Jumlah_Tersedia);
    }
    fclose(file);
}
