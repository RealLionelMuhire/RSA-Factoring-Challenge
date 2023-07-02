#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void factor(mpz_t num) {
    mpz_t two;
    mpz_t sqn;
    mpz_init(two);
    mpz_init(sqn);

    mpz_set_ui(two, 2);
    mpz_sqrt(sqn, num);

    if (mpz_even_p(num)) {
        mpz_divexact_ui(num, num, 2);
        gmp_printf("%Zd*%Zd\n", num, two);
    } else {
        if (mpz_even_p(sqn)) {
            mpz_add_ui(sqn, sqn, 1);
        }

        mpz_t i;
        mpz_init_set_ui(i, 3);
        mpz_t rem;
        mpz_init(rem);

        while (mpz_cmp(i, sqn) <= 0) {
            mpz_tdiv_r(rem, num, i);
            if (mpz_cmp_ui(rem, 0) == 0) {
                mpz_tdiv_q(num, num, i);
                gmp_printf("%Zd*%Zd\n", i, num);
                break;
            }
            mpz_add_ui(i, i, 2);
        }

        if (mpz_cmp(i, sqn) > 0) {
            gmp_printf("%Zd=%Zd*1\n", num, num);
        }

        mpz_clear(i);
        mpz_clear(rem);
    }

    mpz_clear(two);
    mpz_clear(sqn);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a file path as an argument!\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File '%s' not found.\n", argv[1]);
        return 1;
    }

    char line[100];
    mpz_t num;
    mpz_init(num);

    while (fgets(line, sizeof(line), file)) {
        mpz_set_str(num, line, 10);
        gmp_printf("%Zd=", num);
        factor(num);
    }

    mpz_clear(num);
    fclose(file);
    return 0;
}

