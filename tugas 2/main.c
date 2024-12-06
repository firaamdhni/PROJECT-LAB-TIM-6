#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

void baca_lirik(const char *filename);
void proses_lirik();
void simpan_kosa_kata(const char *filename);

int main() {
    baca_lirik("lirik.txt");
    proses_lirik();
    simpan_kosa_kata("kosa-kata.word");

    printf("Proses selesai. File kosa kata.word telah dibuat.\n");
    return 0;
}
