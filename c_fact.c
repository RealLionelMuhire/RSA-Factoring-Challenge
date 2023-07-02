#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void factor(mpz_t n) {
    mpz_t factor_num;
    mpz_init(factor_num);

    gmp_printf("%Zd=", n);

    mpz_t x, y, d;
    mpz_init(x);
    mpz_init(y);
    mpz_init(d);

    mpz_set_ui(x, 2);
    mpz_set_ui(y, 2);

    while (mpz_cmp_ui(d, 1) == 0) {
        mpz_mul(x, x, x);
        mpz_add_ui(x, x, 1);
        mpz_mod(x, x, n);

        mpz_mul(y, y, y);
        mpz_add_ui(y, y, 1);
        mpz_mod(y, y, n);

        mpz_sub(d, x, y);
        mpz_abs(d, d);
        mpz_gcd(d, d, n);
    }

    if (mpz_cmp(d, n) == 0) {
        gmp_printf("%Zd is prime\n", n);
    } else {
        gmp_printf("%Zd*", d);
        mpz_divexact(n, n, d);
        factor(n);
    }

    mpz_clear(factor_num);
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(d);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a file path as an argument!\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File '%s' not found.\n", argv[1]);
        return 0;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        mpz_t num;
        mpz_init(num);
        mpz_set_str(num, line, 10);
        factor(num);
        mpz_clear(num);
    }

    fclose(file);

    return 0;
}

