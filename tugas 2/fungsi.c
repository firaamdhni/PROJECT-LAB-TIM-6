#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

#define MAX_WORDS 1000
#define MAX_LENGTH 100

// Struktur untuk menyimpan daftar kosa kata
char kosa_kata[MAX_WORDS][MAX_LENGTH];
int jumlah_kosa_kata = 0;
char judul_lagu[MAX_LENGTH];

// Fungsi untuk membaca lirik dari file
void baca_lirik(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Gagal membuka file");
        exit(1);
    }

    // Membaca judul lagu
    fgets(judul_lagu, MAX_LENGTH, file);
    // Menghilangkan newline di akhir judul
    judul_lagu[strcspn(judul_lagu, "\n")] = '\0';
    
    fclose(file);
}

// Fungsi untuk memproses lirik dan menemukan kosa kata unik
void proses_lirik() {
    FILE *file = fopen("lirik.txt", "r");
    if (file == NULL) {
        perror("Gagal membuka file");
        exit(1);
    }

    char word[MAX_LENGTH];
    fgets(word, MAX_LENGTH, file);
    while (fscanf(file, "%s", word) != EOF) {
        // Mengubah setiap kata menjadi huruf kecil dan menghapus tanda baca
        int i = 0;
        while (word[i]) {
            word[i] = tolower(word[i]);
            i++;
        }

        // Menghapus tanda baca selain tanda hubung
        int len = strlen(word);
        for (i = 0; i < len; i++) {
            if (!(isalnum(word[i]) || word[i] == '\'' || word[i] == '-')) {
                for (int j = i; j < len; j++) {
                    word[j] = word[j + 1];
                }
                len--;
                i--;
            }
        }

        // Memeriksa apakah kata sudah ada dalam daftar kosa kata
        int found = 0;
        for (i = 0; i < jumlah_kosa_kata; i++) {
            if (strcmp(kosa_kata[i], word) == 0) {
                found = 1;
                break;
            }
        }

        // Jika kata belum ada, tambahkan ke daftar kosa kata
        if (!found) {
            strcpy(kosa_kata[jumlah_kosa_kata], word);
            jumlah_kosa_kata++;
        }
    }

    fclose(file);
}

// Fungsi untuk menyimpan kosa kata ke dalam file
void simpan_kosa_kata(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Gagal membuka file untuk menulis");
        exit(1);
    }

    // Menulis judul lagu
    fprintf(file, "%s\n", judul_lagu);

    // Menulis setiap kosa kata
    for (int i = 0; i < jumlah_kosa_kata; i++) {
        fprintf(file, "%s=\n", kosa_kata[i]);
    }

    fclose(file);
}
