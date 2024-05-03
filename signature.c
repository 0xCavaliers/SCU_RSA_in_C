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
    mpz_t n, d, message, signature;

    // 初始化 mpz_t 变量
    mpz_init(n);
    mpz_init(d);
    mpz_init(message);
    mpz_init(signature);

    // 读取明文和私钥
    read_hex_from_file("rsa_plain.txt", message, 1);
    read_hex_from_file("rsa_prikey.txt", n, 1); // n 在第一行
    read_hex_from_file("rsa_prikey.txt", d, 2); // d 在第二行

    // 使用私钥签名消息
    mpz_powm(signature, message, d, n); // 模幂函数

    // 将签名写入文件
    write_hex_to_file(signature, "rsa_sign.txt");

    // 清理 mpz_t 变量
    mpz_clear(n);
    mpz_clear(d);
    mpz_clear(message);
    mpz_clear(signature);

    printf("数据签名完成并已写入文件 rsa_sign.txt\n");

    return 0;
}
