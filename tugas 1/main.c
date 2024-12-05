#include "header.h"

int main(int argc, char *argv[]) {
    char role[10];

    // Muat data alat dari file
    data();

    // Cek login berdasarkan metode (CLA atau interaktif)
    if (argc == 4) {
        // Login dengan Command Line Argument
        if (!login_with_cla(argv[1], argv[2], argv[3])) {
            printf("Login gagal dengan Command Line Argument.\n");
            return 1;
        }
        strcpy(role, argv[1]);
    } else {
        // Login interaktif
        if (!login(role)) {
            return 1;
        }
    }
