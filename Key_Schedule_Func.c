#include "main.h"
#include "OP_TABLEh.h"

//키스케줄 과정에서 쓰이는 상수값
const word Rcon[10] = { 0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,0x40000000,0x80000000,0x1b000000,0x36000000 };

word RotWord(word input) {
	return ((input << 8) | (input >> 24));
}

word SubWord(word input) {
	return (((sbox[input >> 24]) << 24) ^ ((sbox[(input >> 16) & 0xff]) << 16) ^ ((sbox[(input >> 8) & 0xff]) << 8) ^ (sbox[input & 0xff]));
}

word KeySchedule_F(word input, int rn) {
	return ((SubWord(RotWord(input))) ^ (Rcon[rn]));
}

//Enc과정에서 쓰이는 KeySchedule 함수
void AES_KeySchedule(uint8_t* key, uint32_t rk[11][4]) {
	int cnt_i, cnt_j;
	for (cnt_i = 0; cnt_i < 4; cnt_i++) {
		rk[0][cnt_i] = GETU32(key + (4 * cnt_i));
	}

	//1ROUND~10ROUND
	for (cnt_i = 1; cnt_i < 11; cnt_i++) {
		for (cnt_j = 0; cnt_j < 4; cnt_j++) {
			if (cnt_j == 0) {
				rk[cnt_i][cnt_j] = (KeySchedule_F(rk[cnt_i - 1][3], (cnt_i - 1)) ^ rk[cnt_i - 1][0]);
			}
			else {
				rk[cnt_i][cnt_j] = (rk[cnt_i][cnt_j - 1] ^ rk[cnt_i - 1][cnt_j]);
			}
		}
	}
}