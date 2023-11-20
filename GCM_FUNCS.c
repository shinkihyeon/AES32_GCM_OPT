#include "main.h"
#include "OP_TABLEh.h"

//in GF(2^128), f에 x를 곱하는 함수
//입력값을 update 해나아가는 방식으로 구현 
void GF128_xtime(byte* f) {
	byte msb = f[15] & 0x01;//여기서 msb 1 or 0인지 판단해야 -> 아래서부터 f는 변질되기 때문에!
	//right shift 1
	*(f + 15) = (*(f + 15) >> 1) | ((*(f + 14) & 0x01) << 7);
	*(f + 14) = (*(f + 14) >> 1) | ((*(f + 13) & 0x01) << 7);
	*(f + 13) = (*(f + 13) >> 1) | ((*(f + 12) & 0x01) << 7);
	*(f + 12) = (*(f + 12) >> 1) | ((*(f + 11) & 0x01) << 7);
	*(f + 11) = (*(f + 11) >> 1) | ((*(f + 10) & 0x01) << 7);
	*(f + 10) = (*(f + 10) >> 1) | ((*(f + 9) & 0x01) << 7);
	*(f + 9) = (*(f + 9) >> 1) | ((*(f + 8) & 0x01) << 7);
	*(f + 8) = (*(f + 8) >> 1) | ((*(f + 7) & 0x01) << 7);
	*(f + 7) = (*(f + 7) >> 1) | ((*(f + 6) & 0x01) << 7);
	*(f + 6) = (*(f + 6) >> 1) | ((*(f + 5) & 0x01) << 7);
	*(f + 5) = (*(f + 5) >> 1) | ((*(f + 4) & 0x01) << 7);
	*(f + 4) = (*(f + 4) >> 1) | ((*(f + 3) & 0x01) << 7);
	*(f + 3) = (*(f + 3) >> 1) | ((*(f + 2) & 0x01) << 7);
	*(f + 2) = (*(f + 2) >> 1) | ((*(f + 1) & 0x01) << 7);
	*(f + 1) = (*(f + 1) >> 1) | ((*(f + 0) & 0x01) << 7);
	//lsb part 해결
	*(f + 0) = *(f + 0) >> 1;
	//msb가 1일때 처리
	if (msb) {
		*(f + 0) ^= 0xE1;
	}
}

////in GF(2^128), f에 8*x를 곱하는 함수
//입력값을 update 하는 방식
void GF128_8xtime(byte* f) {
	//(7차 다항식) * x^128 처리 위해서 미리 복사
	byte temp = f[15];
	//이동 꼬이지 x -> 15에서 1로
	*(f + 15) = *(f + 14);
	*(f + 14) = *(f + 13);
	*(f + 13) = *(f + 12);
	*(f + 12) = *(f + 11);
	*(f + 11) = *(f + 10);
	*(f + 10) = *(f + 9);
	*(f + 9) = *(f + 8);
	*(f + 8) = *(f + 7);
	*(f + 7) = *(f + 6);
	*(f + 6) = *(f + 5);
	*(f + 5) = *(f + 4);
	*(f + 4) = *(f + 3);
	*(f + 3) = *(f + 2);
	*(f + 2) = *(f + 1);
	*(f + 1) = *(f + 0);
	//HT2 이용해서 마무리
	f[0] = HT2[temp][0];
	f[1] ^= HT2[temp][1];
}


//FOR문을 사용x -> 속도 증가
//GHASH 과정 중 -> 16바이트 한 블록 * H(Enc(0^128, key))
//Xi * H -> Xi
void GF128_MUL_OPT(byte* f) {
	byte temp[16] = { 0, };
	//15
	memcpy(temp, HT1[*(f + 15)], 16 * sizeof(byte));
	GF128_8xtime(temp);
	//14
	*(temp + 0) ^= *(HT1[*(f + 14)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 14)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 14)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 14)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 14)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 14)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 14)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 14)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 14)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 14)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 14)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 14)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 14)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 14)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 14)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 14)] + 15);
	GF128_8xtime(temp);
	//13
	*(temp + 0) ^= *(HT1[*(f + 13)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 13)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 13)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 13)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 13)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 13)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 13)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 13)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 13)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 13)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 13)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 13)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 13)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 13)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 13)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 13)] + 15);
	GF128_8xtime(temp);
	//12
	*(temp + 0) ^= *(HT1[*(f + 12)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 12)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 12)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 12)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 12)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 12)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 12)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 12)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 12)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 12)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 12)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 12)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 12)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 12)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 12)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 12)] + 15);
	GF128_8xtime(temp);
	//11
	*(temp + 0) ^= *(HT1[*(f + 11)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 11)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 11)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 11)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 11)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 11)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 11)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 11)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 11)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 11)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 11)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 11)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 11)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 11)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 11)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 11)] + 15);
	GF128_8xtime(temp);
	//10
	*(temp + 0) ^= *(HT1[*(f + 10)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 10)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 10)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 10)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 10)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 10)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 10)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 10)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 10)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 10)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 10)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 10)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 10)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 10)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 10)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 10)] + 15);
	GF128_8xtime(temp);
	//9
	*(temp + 0) ^= *(HT1[*(f + 9)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 9)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 9)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 9)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 9)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 9)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 9)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 9)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 9)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 9)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 9)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 9)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 9)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 9)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 9)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 9)] + 15);
	GF128_8xtime(temp);
	//8
	*(temp + 0) ^= *(HT1[*(f + 8)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 8)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 8)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 8)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 8)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 8)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 8)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 8)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 8)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 8)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 8)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 8)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 8)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 8)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 8)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 8)] + 15);
	GF128_8xtime(temp);
	//7
	*(temp + 0) ^= *(HT1[*(f + 7)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 7)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 7)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 7)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 7)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 7)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 7)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 7)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 7)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 7)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 7)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 7)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 7)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 7)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 7)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 7)] + 15);
	GF128_8xtime(temp);
	//6
	*(temp + 0) ^= *(HT1[*(f + 6)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 6)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 6)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 6)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 6)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 6)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 6)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 6)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 6)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 6)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 6)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 6)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 6)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 6)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 6)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 6)] + 15);
	GF128_8xtime(temp);
	//5
	*(temp + 0) ^= *(HT1[*(f + 5)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 5)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 5)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 5)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 5)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 5)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 5)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 5)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 5)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 5)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 5)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 5)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 5)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 5)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 5)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 5)] + 15);
	GF128_8xtime(temp);
	//4
	*(temp + 0) ^= *(HT1[*(f + 4)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 4)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 4)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 4)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 4)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 4)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 4)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 4)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 4)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 4)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 4)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 4)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 4)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 4)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 4)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 4)] + 15);
	GF128_8xtime(temp);
	//3
	*(temp + 0) ^= *(HT1[*(f + 3)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 3)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 3)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 3)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 3)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 3)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 3)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 3)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 3)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 3)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 3)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 3)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 3)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 3)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 3)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 3)] + 15);
	GF128_8xtime(temp);
	//2
	*(temp + 0) ^= *(HT1[*(f + 2)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 2)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 2)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 2)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 2)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 2)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 2)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 2)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 2)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 2)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 2)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 2)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 2)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 2)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 2)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 2)] + 15);
	GF128_8xtime(temp);
	//1
	*(temp + 0) ^= *(HT1[*(f + 1)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 1)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 1)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 1)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 1)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 1)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 1)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 1)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 1)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 1)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 1)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 1)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 1)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 1)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 1)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 1)] + 15);
	GF128_8xtime(temp);
	//0 -> GF128_8xtime() 과정 X
	*(temp + 0) ^= *(HT1[*(f + 0)] + 0);
	*(temp + 1) ^= *(HT1[*(f + 0)] + 1);
	*(temp + 2) ^= *(HT1[*(f + 0)] + 2);
	*(temp + 3) ^= *(HT1[*(f + 0)] + 3);
	*(temp + 4) ^= *(HT1[*(f + 0)] + 4);
	*(temp + 5) ^= *(HT1[*(f + 0)] + 5);
	*(temp + 6) ^= *(HT1[*(f + 0)] + 6);
	*(temp + 7) ^= *(HT1[*(f + 0)] + 7);
	*(temp + 8) ^= *(HT1[*(f + 0)] + 8);
	*(temp + 9) ^= *(HT1[*(f + 0)] + 9);
	*(temp + 10) ^= *(HT1[*(f + 0)] + 10);
	*(temp + 11) ^= *(HT1[*(f + 0)] + 11);
	*(temp + 12) ^= *(HT1[*(f + 0)] + 12);
	*(temp + 13) ^= *(HT1[*(f + 0)] + 13);
	*(temp + 14) ^= *(HT1[*(f + 0)] + 14);
	*(temp + 15) ^= *(HT1[*(f + 0)] + 15);
	//RESULT PART
	memcpy(f, temp, 16 * sizeof(byte));
}

//GHASH 고속화 VER by 사전계산한 table
void GHASH_OPT(byte* X, word x_len, byte* result) {
	//X1
	GF128_MUL_OPT(X);
	//X2,X3,.......
	int i;
	int loop_len = (x_len / 16) - 1;
	for (i = 1; i < (loop_len + 1); i++) {
		*(X + (0 + 16 * i)) ^= *(X + (0 + 16 * (i - 1)));
		*(X + (1 + 16 * i)) ^= *(X + (1 + 16 * (i - 1)));
		*(X + (2 + 16 * i)) ^= *(X + (2 + 16 * (i - 1)));
		*(X + (3 + 16 * i)) ^= *(X + (3 + 16 * (i - 1)));
		*(X + (4 + 16 * i)) ^= *(X + (4 + 16 * (i - 1)));
		*(X + (5 + 16 * i)) ^= *(X + (5 + 16 * (i - 1)));
		*(X + (6 + 16 * i)) ^= *(X + (6 + 16 * (i - 1)));
		*(X + (7 + 16 * i)) ^= *(X + (7 + 16 * (i - 1)));
		*(X + (8 + 16 * i)) ^= *(X + (8 + 16 * (i - 1)));
		*(X + (9 + 16 * i)) ^= *(X + (9 + 16 * (i - 1)));
		*(X + (10 + 16 * i)) ^= *(X + (10 + 16 * (i - 1)));
		*(X + (11 + 16 * i)) ^= *(X + (11 + 16 * (i - 1)));
		*(X + (12 + 16 * i)) ^= *(X + (12 + 16 * (i - 1)));
		*(X + (13 + 16 * i)) ^= *(X + (13 + 16 * (i - 1)));
		*(X + (14 + 16 * i)) ^= *(X + (14 + 16 * (i - 1)));
		*(X + (15 + 16 * i)) ^= *(X + (15 + 16 * (i - 1)));
		GF128_MUL_OPT(X + (16 * i));
	}
	//출력값
	memcpy(result, X + 16 * loop_len, 16 * sizeof(byte));
}



//result -> C||tag -> 암호문 C, 인증값에 해당하는 tag 값을 CONCAT
//result배열의 크기는 C_len + tag_len -> main함수에서 미리 지역변수 크기로 미리 잡아서 줄것
//참고)CTR모드에서는 패딩과정이 없기 때문에 암호문길이와 평문의 길이는 같다.
void AES32_GCM_OPT(byte* pt, int pt_len, byte* key, byte* IV, byte* AD, int AD_len, int tag_len, byte* result) {
	//J0->CIPHK(J0) -> 마지막처리에서 쓰일거 -> 미리 복사해두자 -> CT구할때 IV에 +1한 값이 초기 카운터라서
	byte J0[16];
	memcpy(J0, IV, 16 * sizeof(byte));

	//GHASH INPUT값에 필요한 정보
	int padded_AD_len = AD_len % 16 == 0 ? AD_len : AD_len + (16 - (AD_len % 16));
	int padded_CT_len = pt_len % 16 == 0 ? pt_len : pt_len + (16 - (pt_len % 16));
	int GH_len = padded_AD_len + padded_CT_len + 16;
	byte* GH_V = (byte*)calloc(GH_len, sizeof(byte));
	assert(GH_V != NULL);

	//pt -> ct by AES32_CTR
	byte* ct = (byte*)calloc(pt_len, sizeof(byte));
	assert(ct != NULL);
	CTR_INC(IV);//IV+1 -> 초기 카운터값
	AES32_CTR(pt, ct, IV, pt_len, key);

	//AD_len,CT_len -> 각각 64-bit로 표현
	//주의)각각의 len은 bit -> AD가 16BYTE면 128을 64BIT로 넣어야 함
	unsigned long long AD_64_len = (unsigned long long)AD_len * 8;
	unsigned long long CT_64_len = (unsigned long long)pt_len * 8;
	byte AD_CT_len[16] = { 0, };
	*(AD_CT_len + 0) = (AD_64_len >> 56) & 0xff;
	*(AD_CT_len + 8) = (CT_64_len >> 56) & 0xff;
	*(AD_CT_len + 1) = (AD_64_len >> 48) & 0xff;
	*(AD_CT_len + 9) = (CT_64_len >> 48) & 0xff;
	*(AD_CT_len + 2) = (AD_64_len >> 40) & 0xff;
	*(AD_CT_len + 10) = (CT_64_len >> 40) & 0xff;
	*(AD_CT_len + 3) = (AD_64_len >> 32) & 0xff;
	*(AD_CT_len + 11) = (CT_64_len >> 32) & 0xff;
	*(AD_CT_len + 4) = (AD_64_len >> 24) & 0xff;
	*(AD_CT_len + 12) = (CT_64_len >> 24) & 0xff;
	*(AD_CT_len + 5) = (AD_64_len >> 16) & 0xff;
	*(AD_CT_len + 13) = (CT_64_len >> 16) & 0xff;
	*(AD_CT_len + 6) = (AD_64_len >> 8) & 0xff;
	*(AD_CT_len + 14) = (CT_64_len >> 8) & 0xff;
	*(AD_CT_len + 7) = (AD_64_len) & 0xff;
	*(AD_CT_len + 15) = (CT_64_len) & 0xff;

	//GH_V(GHASH INPUT VALUE)값을 채워넣어야지
	memcpy(GH_V, AD, AD_len * sizeof(byte));
	memset(GH_V + AD_len, 0, (padded_AD_len - AD_len) * sizeof(byte));
	memcpy(GH_V + padded_AD_len, ct, pt_len * sizeof(byte));
	memset(GH_V + padded_AD_len + pt_len, 0, (padded_CT_len - pt_len) * sizeof(byte));
	memcpy(GH_V + padded_AD_len + padded_CT_len, AD_CT_len, 16 * sizeof(byte));

	//GHASH
	byte GHASH_OUTPUT[16];
	GHASH_OPT(GH_V, GH_len, GHASH_OUTPUT);

	//AES32(J0)
	byte E_J0[16];
	AES_ENC(J0, key, E_J0);

	//TAG 출력
	byte TAG[16] = { 0, };
	*(TAG + 0) = *(GHASH_OUTPUT + 0) ^ *(E_J0 + 0);
	*(TAG + 1) = *(GHASH_OUTPUT + 1) ^ *(E_J0 + 1);
	*(TAG + 2) = *(GHASH_OUTPUT + 2) ^ *(E_J0 + 2);
	*(TAG + 3) = *(GHASH_OUTPUT + 3) ^ *(E_J0 + 3);
	*(TAG + 4) = *(GHASH_OUTPUT + 4) ^ *(E_J0 + 4);
	*(TAG + 5) = *(GHASH_OUTPUT + 5) ^ *(E_J0 + 5);
	*(TAG + 6) = *(GHASH_OUTPUT + 6) ^ *(E_J0 + 6);
	*(TAG + 7) = *(GHASH_OUTPUT + 7) ^ *(E_J0 + 7);
	*(TAG + 8) = *(GHASH_OUTPUT + 8) ^ *(E_J0 + 8);
	*(TAG + 9) = *(GHASH_OUTPUT + 9) ^ *(E_J0 + 9);
	*(TAG + 10) = *(GHASH_OUTPUT + 10) ^ *(E_J0 + 10);
	*(TAG + 11) = *(GHASH_OUTPUT + 11) ^ *(E_J0 + 11);
	*(TAG + 12) = *(GHASH_OUTPUT + 12) ^ *(E_J0 + 12);
	*(TAG + 13) = *(GHASH_OUTPUT + 13) ^ *(E_J0 + 13);
	*(TAG + 14) = *(GHASH_OUTPUT + 14) ^ *(E_J0 + 14);
	*(TAG + 15) = *(GHASH_OUTPUT + 15) ^ *(E_J0 + 15);

	//출력값 -> CT||TAG(tag_len)
	memcpy(result, ct, pt_len * sizeof(byte));
	memcpy(result + pt_len, TAG, tag_len * sizeof(byte));

	//동적메모리 해제
	free(ct);
	free(GH_V);
	ct = NULL;
	GH_V = NULL;
}