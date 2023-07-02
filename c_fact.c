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

        while (mpz_even_p(num)) {
            printf("2*");
            mpz_divexact_ui(num, num, 2);
        }

        if (mpz_cmp_ui(num, 1) <= 0) {
            printf("1\n");
        } else {
            mpz_t i, x, y, factor;
            mpz_init(i);
            mpz_init(x);
            mpz_init(y);
            mpz_init(factor);
            mpz_set_ui(i, 1);
            mpz_set_ui(x, 2);
            mpz_set_ui(y, 2);
            mpz_set_ui(factor, 1);

            while (mpz_cmp_ui(factor, 1) == 0) {
                mpz_add_ui(i, i, 1);
                mpz_mul(x, x, x);
                mpz_add_ui(x, x, 1);
                mpz_mod(x, x, num);

                mpz_mul(y, y, y);
                mpz_add_ui(y, y, 1);
                mpz_mod(y, y, num);

                mpz_sub(factor, x, y);
                mpz_abs(factor, factor);
                mpz_gcd(factor, factor, num);
            }

            gmp_printf("%Zd\n", factor);

            mpz_clear(i);
            mpz_clear(x);
            mpz_clear(y);
            mpz_clear(factor);
        }

        mpz_clear(num);
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

