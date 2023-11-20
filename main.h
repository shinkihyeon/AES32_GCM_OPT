#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

typedef unsigned char byte;
typedef unsigned int word;

//Trans_Data_Type
word GETU32(byte* b);
void int2byte(word* input, byte* output);
void byte2int(byte* input, word* output);

//Key_Schedule_Func
word RotWord(word input);
word SubWord(word input);
word KeySchedule_F(word input, int rn);
void AES_KeySchedule(uint8_t* key, uint32_t rk[11][4]);

//GF_Func
byte GF_add(byte op1, byte op2);
byte GF_xtime(byte gf);
byte GF_mul(byte op1, byte op2);


//Enc
void ENC_ROUND(word* input, word* rk);
void AES_ENC(byte* pt, byte* mk, byte* ct);

//AES32_CTR
void CTR_INC(byte* ICTR);
void AES32_CTR(byte* pt, byte* ct, byte* iv, word pt_len, byte* key);

//Gen_H1_TABLE
void HT1_GF128_mul(byte f, byte* g, byte* result);
void gen_table1(byte* key);

//GCM_FUNCS
void GF128_xtime(byte* f);
void GF128_8xtime(byte* f);
void GF128_MUL_OPT(byte* f);
void GHASH_OPT(byte* X, word x_len, byte* result);
void AES32_GCM_OPT(byte* pt, int pt_len, byte* key, byte* IV, byte* AD, int AD_len, int tag_len, byte* result);

//Print_FUNC
void GCM_printstate(byte* result, word size);
