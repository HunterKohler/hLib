#include "common.h"

uint64_t des(uint64_t input, uint64_t key, bool encrypt);

uint64_t des_f(uint64_t r, uint64_t k);
uint64_t *des_key_schedule(uint64_t key, uint64_t *keylist);

uint64_t des_IP(uint64_t x);
uint64_t des_IP_inv(uint64_t x);
uint64_t des_E(uint64_t x);
uint64_t des_S(uint64_t x, size_t n);
uint64_t des_PC_1(uint64_t x);
uint64_t des_PC_2(uint64_t x);
uint64_t des_LS(uint64_t k, size_t n);
uint64_t des_P(uint64_t x);

const byte_t des_table_IP[64];
const byte_t des_table_IP_inv[64];
const byte_t des_table_E[48];
const byte_t des_table_S[8][64];
const byte_t des_table_P[32];
const byte_t des_table_PC_1[56];
const byte_t des_table_PC_2[48];
const byte_t des_table_LS[16];