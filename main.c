#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

void read_hex_from_file(const char *filename, mpz_t value) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    mpz_inp_str(value, file, 16);
    fclose(file);
}

void write_hex_to_file(mpz_t value, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    mpz_out_str(file, 16, value);
    fclose(file);
}

void perform_rsa(const char *plainfile, const char *nfile, const char *keyfile, const char *cipherfile, int is_encryption) {
    mpz_t n, key, plaintext, result;

    // Initialize mpz_t variables
    mpz_init(n);
    mpz_init(key);
    mpz_init(plaintext);
    mpz_init(result);

    // Read plaintext and key
    read_hex_from_file(plainfile, plaintext);
    read_hex_from_file(nfile, n);
    read_hex_from_file(keyfile, key);

    // Perform RSA operation
    mpz_powm(result, plaintext, key, n); // Modular exponentiation

    // Write the result to file
    write_hex_to_file(result, cipherfile);

    // Clear mpz_t variables
    mpz_clear(n);
    mpz_clear(key);
    mpz_clear(plaintext);
    mpz_clear(result);

    printf("操作已完成，结果已写入 %s\n", cipherfile);
}

int main(int argc, char *argv[]) {
    char *plainfile = NULL;
    char *nfile = NULL;
    char *efile = NULL;
    char *dfile = NULL;
    char *cipherfile = NULL;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            plainfile = argv[++i];
        } else if (strcmp(argv[i], "-n") == 0) {
            nfile = argv[++i];
        } else if (strcmp(argv[i], "-e") == 0) {
            efile = argv[++i];
        } else if (strcmp(argv[i], "-d") == 0) {
            dfile = argv[++i];
        } else if (strcmp(argv[i], "-c") == 0) {
            cipherfile = argv[++i];
        }
    }

    if (plainfile == NULL || nfile == NULL || cipherfile == NULL || (efile == NULL && dfile == NULL)) {
        fprintf(stderr, "Usage: %s -p plainfile -n nfile [-e efile] [-d dfile] -c cipherfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Check if we are encrypting or signing
    if (efile != NULL) {
        perform_rsa(plainfile, nfile, efile, cipherfile, 1);
    } else {
        perform_rsa(plainfile, nfile, dfile, cipherfile, 0);
    }

    return EXIT_SUCCESS;
}
