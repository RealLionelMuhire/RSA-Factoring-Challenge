#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>

void rsa(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        printf("File '%s' not found.\n", file_path);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        mpz_t num;
        mpz_init(num);
        mpz_set_str(num, line, 10);

        gmp_printf("%Zd=", num);

        if (mpz_cmp_ui(num, 2) < 0) {
            gmp_printf("%Zd\n", num);
            continue;
        }

        mpz_t i, factor;
        mpz_init(i);
        mpz_init(factor);
        mpz_set_ui(i, 2);
        mpz_set_ui(factor, 1);

        while (mpz_cmp(i, num) <= 0) {
            if (mpz_divisible_p(num, i)) {
                mpz_divexact(factor, num, i);
                break;
            }
            mpz_add_ui(i, i, 1);
        }

        gmp_printf("%Zd*%Zd\n", factor, i);

        mpz_clear(num);
        mpz_clear(i);
        mpz_clear(factor);
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide a file path as argument!\n");
        return 0;
    }

    rsa(argv[1]);

    return 0;
}

