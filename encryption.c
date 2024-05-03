#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// 读取十六进制数值并初始化 mpz_t 变量
void read_hex_from_file(const char *filename, mpz_t value, int line_number) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    int current_line = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        if (++current_line == line_number) {
            mpz_set_str(value, buffer, 16);
            break;
        }
    }
    fclose(file);
}

// 将 mpz_t 变量的值以十六进制形式写入文件
void write_hex_to_file(mpz_t value, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    mpz_out_str(file, 16, value);
    fclose(file);
}

int main() {
    mpz_t n, e, message, encrypted_message;

    // 初始化 mpz_t 变量
    mpz_init(n);
    mpz_init(e);
    mpz_init(message);
    mpz_init(encrypted_message);

    // 读取明文和公钥
    read_hex_from_file("rsa_plain.txt", message, 1);
    read_hex_from_file("rsa_pubkey.txt", n, 1); // 假设 n 在第一行
    read_hex_from_file("rsa_pubkey.txt", e, 2); // 假设 e 在第二行

    // 使用公钥加密消息
    mpz_powm(encrypted_message, message, e, n); // 模幂函数

    // 将加密后的消息写入文件
    write_hex_to_file(encrypted_message, "rsa_cipher.txt");

    // 清理 mpz_t 变量
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(message);
    mpz_clear(encrypted_message);

    printf("数据加密完成并已写入文件 rsa_cipher.txt\n");

    return 0;
}
