#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALAT 100
#define MAX_PINJAMAN 100

// Struktur untuk alat laboratorium
typedef struct {
    unsigned int Id_Alat;
    char Nama_Alat[50];
    char Merek[50];
    char Model[50];
    unsigned int Tahun_Produksi;
    unsigned int Jumlah_Unit;
    unsigned int Jumlah_Tersedia;
} Alat_Lab;

// Struktur untuk peminjaman
typedef struct {
    unsigned int Id_Alat;
    char Nama_Alat[50];
    unsigned int Jumlah_Pinjam;
} Peminjaman;

// Deklarasi variabel global
extern Alat_Lab alat_lab[MAX_ALAT];
extern unsigned int total_alat;
extern Peminjaman peminjaman[MAX_PINJAMAN];
extern unsigned int total_peminjaman;

// Deklarasi fungsi
void data();
void simpan_data();
int login_with_cla(const char *role, const char *username, const char *password);
void cetak_alat();
void admin_menu();
void user_menu();
int login(char *role);
void pinjam_alat();
void lihat_alat_pinjam();
void kembalikan_alat();

#endif

