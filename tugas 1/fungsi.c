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

// Menu Admin
void admin_menu() {
    int pilih;
    do {
        printf("\n Selamat Datang Admin! \n");
        printf("\n---- Menu Admin ----\n");
        printf("1. Tambah Alat Lab\n");
        printf("2. Lihat Daftar Alat Lab\n");
        printf("3. Edit Alat Lab\n");
        printf("4. Hapus Alat Lab\n");
        printf("5. Keluar\n");
        printf("Pilih Opsi: ");
        scanf("%d", &pilih);

        if (pilih == 1) {
            if (total_alat >= MAX_ALAT) {
                printf("Jumlah Alat Lab Mencapai Batas Maksimum.\n");
                continue;
            }

            printf("Masukkan ID Alat: ");
            scanf("%u", &alat.Id_Alat);
            printf("Ma Alat_Lab alat;sukkan Nama Alat: ");
            scanf("%s", alat.Nama_Alat);
            printf("Masukkan Merek: ");
            scanf("%s", alat.Merek);
            printf("Masukkan Model: ");
            scanf("%s", alat.Model);
            printf("Masukkan Tahun Produksi: ");
            scanf("%u", &alat.Tahun_Produksi);
            printf("Masukkan Jumlah Unit: ");
            scanf("%u", &alat.Jumlah_Unit);
            alat.Jumlah_Tersedia = alat.Jumlah_Unit;
            alat_lab[total_alat++] = alat;
            simpan_data();
            printf("Alat Lab Berhasil Ditambahkan.\n");
        } else if (pilih == 2) {
            printf("\n---- Daftar Alat Lab ----\n");
            printf("----------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-10s | %-20s | %-15s | %-15s | %-15s | %-12s | %-15s |\n",
            "ID Alat", "Nama Alat", "Merek", "Model", "Tahun Produksi", "Jumlah Unit", "Jumlah Tersedia");  
            printf("----------------------------------------------------------------------------------------------------------------------------\n");
            for (unsigned int i = 0; i < total_alat; i++) {
                printf("| %-10u | %-20s | %-15s | %-15s | %-15u | %-12u | %-15u |\n",
                alat_lab[i].Id_Alat,
                alat_lab[i].Nama_Alat,
                alat_lab[i].Merek,
                alat_lab[i].Model,
                alat_lab[i].Tahun_Produksi,
                alat_lab[i].Jumlah_Unit,
                alat_lab[i].Jumlah_Tersedia);
        }
            printf("----------------------------------------------------------------------------------------------------------------------------\n");

        } else if (pilih == 3) {
            unsigned int Id_Alat;
            printf("Masukkan ID Alat yang Akan Diedit: ");
            scanf("%u", &Id_Alat);
            int exists = 0;
            for (unsigned int i = 0; i < total_alat; i++) {
                if (alat_lab[i].Id_Alat == Id_Alat) {
                    exists = 1;
                   
                  
                    printf("Masukkan Jumlah Unit: ");
                    scanf("%u", &alat_lab[i].Jumlah_Unit);
                    alat_lab[i].Jumlah_Tersedia = alat_lab[i].Jumlah_Unit;
                    simpan_data();
                    printf("Alat Lab Dengan ID %u Berhasil Diedit.\n", Id_Alat);
                    break;
                }
            }
            if (!exists) {
                printf("Alat Lab Dengan ID %u Tidak Ditemukan.\n", Id_Alat);
            }
        } else if (pilih == 4) {
            unsigned int Id_Alat;
            printf("Masukkan ID Alat yang Akan Dihapus: ");
            scanf("%u", &Id_Alat);
            int exists = 0;
            for (unsigned int i = 0; i < total_alat; i++) {
                if (alat_lab[i].Id_Alat == Id_Alat) {
                    exists = 1;
                    for (unsigned int j = i; j < total_alat - 1; j++) {
                        alat_lab[j] = alat_lab[j + 1];
                    }
                    total_alat--;
                    simpan_data();
                    printf("Alat Lab dengan ID %u Berhasil Dihapus.\n", Id_Alat);
                    break;
                }
            }

            if (!exists) {
                printf("Alat Lab dengan id %u Tidak Ditemukan.\n", Id_Alat);
            }
        }
    } while (pilih != 5);
}

// Fungsi menu user
void user_menu() {
    int pilih;
    do {
        printf("\n Selamat Datang User! \n");
        printf("\n---- Menu User ----\n");
        printf("1. Lihat Daftar Alat Lab\n");
        printf("2. Pinjam Alat\n");
        printf("3. Lihat Alat yang Dipinjam\n");
        printf("4. Kembalikan Alat\n");
        printf("5. Keluar\n");
        printf("Pilih Opsi: ");
        scanf("%d", &pilih);

        if (pilih == 1) {
            printf("\n---- Daftar Alat Lab ----\n");
            printf("-------------------------------------------------------------------------------------------------------------\n");
            printf("| %-10s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", 
            "ID Alat", "Nama Alat", "Merek", "Model", "Tahun", "Jumlah Tersedia" );
            printf("-------------------------------------------------------------------------------------------------------------\n");
            for (unsigned int i = 0; i < total_alat; i++) {
                printf("| %-10u | %-20s | %-15s | %-15s | %-15u | %-15u |\n",
                       alat_lab[i].Id_Alat,
                       alat_lab[i].Nama_Alat,
                       alat_lab[i].Merek,
                       alat_lab[i].Model,
                       alat_lab[i].Tahun_Produksi,
                       alat_lab[i].Jumlah_Tersedia);
            }
            printf("-------------------------------------------------------------------------------------------------------------\n");
        } else if (pilih == 2) {
            pinjam_alat();
        } else if (pilih == 3) {
            lihat_alat_pinjam();
        } else if (pilih == 4) {
            kembalikan_alat();
        }
    } while (pilih != 5);
}
int login(char *role) {
    FILE *file = fopen("user.txt", "r");
    if (file == NULL) {
        printf("File user.txt tidak ditemukan.\n");
        return 0;
    }
    char username[50], password[50], input_user[50], input_pass[50];
    char user_role[10];
    
    printf("Login sebagai (admin/user): ");
    scanf("%s", role); // Pilih role

    if (strcmp(role, "admin") != 0 && strcmp(role, "user") != 0) {
        printf("Role tidak valid. Program keluar.\n");
        fclose(file);
        return 0;
    }

    printf("Masukkan username: ");
    scanf("%s", input_user);
    printf("Masukkan password: ");
    scanf("%s", input_pass);

    // Membaca file user.txt untuk mencocokkan username, password, dan role
    while (fscanf(file, "%49[^,],%49[^,],%9[^\n]\n", username, password, user_role) != EOF) {
        if (strcmp(input_user, username) == 0 && strcmp(input_pass, password) == 0 && strcmp(user_role, role) == 0) {
            fclose(file);
            return 1; // Login berhasil
        }
    }

    fclose(file);
    printf("Login gagal. Username, password, atau role tidak sesuai.\n");
    return 0; // Login gagal
}

// Fungsi untuk pinjam alat
void pinjam_alat() {
    unsigned int id_alat, jumlah;
    printf("Masukkan ID Alat yang ingin dipinjam: ");
    scanf("%u", &id_alat);

    printf("Masukkan jumlah alat yang ingin dipinjam: ");
    scanf("%u", &jumlah);
    
    // Cek apakah alat ada dan tersedia
    int found = 0;
    for (unsigned int i = 0; i < total_alat; i++) {
        if (alat_lab[i].Id_Alat == id_alat) {
            found = 1;
            if (alat_lab[i].Jumlah_Tersedia >= jumlah) {
                // Jika alat tersedia
                peminjaman[total_peminjaman].Id_Alat = id_alat;
                strcpy(peminjaman[total_peminjaman].Nama_Alat, alat_lab[i].Nama_Alat);
                peminjaman[total_peminjaman].Jumlah_Pinjam = jumlah;

                alat_lab[i].Jumlah_Tersedia -= jumlah;
                total_peminjaman++;
                simpan_data();
                printf("Alat berhasil dipinjam.\n");
            } else {
                printf("Jumlah alat yang tersedia tidak cukup.\n");
            }
            break;
        }
    }
    if (!found) {
        printf("Alat dengan ID %u tidak ditemukan.\n", id_alat);
    }
}


// Fungsi untuk melihat alat yang dipinjam
void lihat_alat_pinjam() {
    printf("\n---- Alat yang Dipinjam ----\n");
    if (total_peminjaman == 0) {
        printf("Belum ada alat yang dipinjam.\n");
    } else {
        printf("-----------------------------------------------------\n");
        printf("| %-10s | %-20s | %-15s |\n", 
         "ID Alat", "Nama Alat", "Jumlah Pinjam"); 
        printf("------------------------------------------------------\n");     
        for (unsigned int i = 0; i < total_peminjaman; i++) {
            printf("| %-10u | %-20s | %-15u |\n",
                   peminjaman[i].Id_Alat,
                   peminjaman[i].Nama_Alat,
                   peminjaman[i].Jumlah_Pinjam);
        }
        printf("-------------------------------------------------------\n");
    }
}

// Fungsi untuk mengembalikan alat
void kembalikan_alat() {
    unsigned int id_alat, jumlah;
    printf("Masukkan ID Alat yang ingin dikembalikan: ");
    scanf("%u", &id_alat);

    printf("Masukkan jumlah alat yang ingin dikembalikan: ");
    scanf("%u", &jumlah);

    // Cek apakah alat yang dipinjam ada
    int found = 0;
    for (unsigned int i = 0; i < total_peminjaman; i++) {
        if (peminjaman[i].Id_Alat == id_alat) {
            found = 1;
            if (peminjaman[i].Jumlah_Pinjam >= jumlah) {
                // Kurangi jumlah yang dipinjam dan kembalikan ke alat lab
                peminjaman[i].Jumlah_Pinjam -= jumlah;
                for (unsigned int j = 0; j < total_alat; j++) {
                    if (alat_lab[j].Id_Alat == id_alat) {
                        alat_lab[j].Jumlah_Tersedia += jumlah;
                        break;
                    }
                }
                // Jika jumlah pinjaman menjadi 0, hapus dari list peminjaman
                if (peminjaman[i].Jumlah_Pinjam == 0) {
                    for (unsigned int j = i; j < total_peminjaman - 1; j++) {
                        peminjaman[j] = peminjaman[j + 1];
                    }
                    total_peminjaman--;
                }
                simpan_data();
                printf("Alat berhasil dikembalikan.\n");
            } else {
                printf("Jumlah alat yang dipinjam lebih sedikit dari jumlah yang ingin dikembalikan.\n");
            }
            break;
        }
    }
    if (!found) {
        printf("Alat dengan ID %u tidak ditemukan dalam daftar peminjaman.\n", id_alat);
    }
}
