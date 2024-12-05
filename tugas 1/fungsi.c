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

// Fungsi login menggunakan Command Line Argument (CLA)
int login_with_cla(const char *role, const char *username, const char *password) {
    FILE *file = fopen("user.txt", "r");
    if (file == NULL) {
        printf("File user.txt tidak ditemukan.\n");
        return 0;
    }

    char file_username[50], file_password[50], file_role[10];
    while (fscanf(file, "%49[^,],%49[^,],%9[^\n]\n", file_username, file_password, file_role) != EOF) {
        if (strcmp(file_username, username) == 0 &&
            strcmp(file_password, password) == 0 &&
            strcmp(file_role, role) == 0) {
            fclose(file);
            return 1; // Login berhasil
        }
    }
    fclose(file);
    return 0; // Login gagal
}

// Fungsi mencetak daftar alat
void cetak_alat() {
    printf("\n---- Daftar Alat Lab ----\n");
    for (unsigned int i = 0; i < total_alat; i++) {
        printf("ID: %u, Nama: %s, Merek: %s, Model: %s, Tahun: %u, Jumlah Unit: %u, Jumlah Tersedia: %u\n",
               alat_lab[i].Id_Alat, alat_lab[i].Nama_Alat, alat_lab[i].Merek,
               alat_lab[i].Model, alat_lab[i].Tahun_Produksi,
               alat_lab[i].Jumlah_Unit, alat_lab[i].Jumlah_Tersedia);
    }
}
