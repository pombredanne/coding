#ifndef __H__MYALGORITHM
#define __H__MYALGORITHM
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>

// RC4 encryption and decryption
void rc4_init(uint8_t *s, uint8_t *key, uint16_t Len);//初始化函数

void rc4_crypt(uint8_t *s, uint8_t *Data, uint16_t Len);//加解密

// Tea encryption and decryption
void tea_encrypt (uint32_t* v, uint32_t* k);//Tea 加密函数

void tea_decrypt (uint32_t* v, uint32_t* k);//Tea 解密函数

void xtea_encypt(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]);//xTea

void xtea_decrypt(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]);//xTea

void xxtea_btea(uint32_t *v, int n, uint32_t const key[4]);//xxTea


// scale exchange
int tolower(int c);/*将大写字母转换成小写字母*/  

int htoi(char s[]);//将十六进制的字符串转换成整数 

int atoi(char s[]);/*将字符串s转换成相应的整数*/  


//
void str_reverse(char *s, int start, int end);



#endif