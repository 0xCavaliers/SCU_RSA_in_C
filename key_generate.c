#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Utility function to generate a random large prime
void generate_prime(mpz_t prime, int bits) {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_urandomb(prime, state, bits);
    mpz_nextprime(prime, prime);
}

// Utility function to calculate gcd
void calculate_gcd(mpz_t result, mpz_t a, mpz_t b) {
    mpz_gcd(result, a, b);
}

// Utility function to calculate modular multiplicative inverse
int calculate_mod_inverse(mpz_t result, mpz_t base, mpz_t mod) {
    return mpz_invert(result, base, mod);
}

void write_to_file(const char *filename, mpz_t data) {
    FILE *file = fopen(filename, "w");  // Open file for writing
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }
    gmp_fprintf(file, "%Zx\n", data);  // Write data as hex to file
    fclose(file);  // Close file
}

int main() {
    int bits = 512; // Use 512 bits for p and q for a total of 1024 bits
    mpz_t p, q, n, phi, e, d, gcd;
    mpz_inits(p, q, n, phi, e, d, gcd, NULL);

    // Generate two large primes p and q
    generate_prime(p, bits);
    generate_prime(q, bits);

    // Calculate n = p * q
    mpz_mul(n, p, q);

    // Calculate phi(n) = (p-1)*(q-1)
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);

    // Select e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1
    mpz_set_ui(e, 65537); // Common choice for e
    calculate_gcd(gcd, e, phi);
    while (mpz_cmp_ui(gcd, 1) != 0) {
        mpz_add_ui(e, e, 1);
        calculate_gcd(gcd, e, phi);
    }

    // Calculate d, the modular multiplicative inverse of e (mod phi(n))
    if (!calculate_mod_inverse(d, e, phi)) {
        printf("Failed to find modular inverse!\n");
        return 1;
    }

    // Write results to files
    write_to_file("p.txt", p);
    write_to_file("q.txt", q);
    write_to_file("n.txt", n);
    write_to_file("e.txt", e);
    write_to_file("d.txt", d);

    // Print the results
    gmp_printf("p = %Zx\nq = %Zx\nn = %Zx\ne = %Zx\nd = %Zx\n", p, q, n, e, d);

    // Clear memory
    mpz_clears(p, q, n, phi, e, d, gcd, NULL);
    return 0;
}
