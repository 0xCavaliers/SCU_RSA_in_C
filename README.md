# SCU_RSA_in_C
川大密码学RSA加密（密钥生成、数据加密、数字签名）实现
以下是在Linux环境下运行教程

## 1.环境配置——GMP库（用来处理大数）的安装
### 1.1 先安装m4
sudo apt-get install m4

### 1.2 安装Zstandard解压工具
sudo apt update
sudo apt install zstd

### 1.3 去去libgmp官网下载最新的gmp包，https://gmplib.org/，例如我下载的是gmp-6.3.0.tar.zst
解压下载的包:
zstd -d gmp-6.3.0.tar.zst -o gmp-6.3.0.tar
tar -xvf gmp-6.3.0.tar

### 1.4 进入解压的目录
cd gmp-6.3.0

### 1.5 环境配置
./configure

### 1.6 完成配置
make
make install

## 2. 代码运行
### 2.1 进入本项目代码文件
make
得到一系列可执行文件

### 2.2 直接运行检验效果
可以使用./encryption等等单独运行

也可以使用命令行的形式：
e3rsa -p plainfile -n nfile [-e efile] [-d dfile] -c cipherfile 
参数：
-p plainfile 指定明文文件的位置和名称
-n nfile 指定存放整数 n 的文件的位置和名称
-e efile 在数据加密时，指定存放整数 e 的文件的位置和名称
-d dfile 在数字签名时，指定存放整数 d 的文件的位置和名称
-c cipherfile 指定密文文件的位置和名称

## 3.其他说明
rsa_plain.txt（明文文件）
rsa_pubkey.txt（公钥，第一行为n，第二行为e，私钥相同）
rsa_prikey.txt（私钥）
rsa_cipher.txt（存数据加密结果）
rsa_sign.txt（存储签名结果）

2024.5.3
