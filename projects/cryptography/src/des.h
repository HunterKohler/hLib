#include "common.h"

uint64_t des(uint64_t input, uint64_t key);
uint64_t des_f(uint64_t r, uint64_t k);
void des_key_schedule(uint64_t key, uint64_t *keylist);

const byte_t des_IP[64];
const byte_t des_IP_inv[64];
const byte_t des_E[48];
const byte_t des_S[8][64];
const byte_t des_P[32];
const byte_t des_PC_1[56];
const byte_t des_PC_2[48];
const byte_t des_LS[16];
