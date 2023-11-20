#include "main.h"

//HT1 ������ �ʿ��� FUNC
//(�־��� 7�� ���׽�) * H(x)
//�ӵ� ������ for���� ������� ����
void HT1_GF128_mul(byte f, byte* g, byte* result) {
	byte temp[16] = { 0, };
	byte mv[16];
	memcpy(mv, g, 16 * sizeof(byte));
	//f -> f0,f1,...f7 1bit�� ����
	//7
	byte cv = (f >> 7) & 0x01;
	if (cv) {
		*(temp + 0) ^= *(mv + 0);
		*(temp + 1) ^= *(mv + 1);
		*(temp + 2) ^= *(mv + 2);
		*(temp + 3) ^= *(mv + 3);
		*(temp + 4) ^= *(mv + 4);
		*(temp + 5) ^= *(mv + 5);
		*(temp + 6) ^= *(mv + 6);
		*(temp + 7) ^= *(mv + 7);
		*(temp + 8) ^= *(mv + 8);
		*(temp + 9) ^= *(mv + 9);
		*(temp + 10) ^= *(mv + 10);
		*(temp + 11) ^= *(mv + 11);
		*(temp + 12) ^= *(mv + 12);
		*(temp + 13) ^= *(mv + 13);
		*(temp + 14) ^= *(mv + 14);
		*(temp + 15) ^= *(mv + 15);
	}
	GF128_xtime(mv);
	//6
	cv = (f >> 6) & 0x01;//f0,f1,...f7 1bit�� ����
	if (cv) {
		*(temp + 0) ^= *(mv + 0);
		*(temp + 1) ^= *(mv + 1);
		*(temp + 2) ^= *(mv + 2);
		*(temp + 3) ^= *(mv + 3);
		*(temp + 4) ^= *(mv + 4);
		*(temp + 5) ^= *(mv + 5);
		*(temp + 6) ^= *(mv + 6);
		*(temp + 7) ^= *(mv + 7);
		*(temp + 8) ^= *(mv + 8);
		*(temp + 9) ^= *(mv + 9);
		*(temp + 10) ^= *(mv + 10);
		*(temp + 11) ^= *(mv + 11);
		*(temp + 12) ^= *(mv + 12);
		*(temp + 13) ^= *(mv + 13);
		*(temp + 14) ^= *(mv + 14);
		*(temp + 15) ^= *(mv + 15);
	}
	GF128_xtime(mv);
	//5
	cv = (f >> 5) & 0x01;//f0,f1,...f7 1bit�� ����
	if (cv) {
		*(temp + 0) ^= *(mv + 0);
		*(temp + 1) ^= *(mv + 1);
		*(temp + 2) ^= *(mv + 2);
		*(temp + 3) ^= *(mv + 3);
		*(temp + 4) ^= *(mv + 4);
		*(temp + 5) ^= *(mv + 5);
		*(temp + 6) ^= *(mv + 6);
		*(temp + 7) ^= *(mv + 7);
		*(temp + 8) ^= *(mv + 8);
		*(temp + 9) ^= *(mv + 9);
		*(temp + 10) ^= *(mv + 10);
		*(temp + 11) ^= *(mv + 11);
		*(temp + 12) ^= *(mv + 12);
		*(temp + 13) ^= *(mv + 13);
		*(temp + 14) ^= *(mv + 14);
		*(temp + 15) ^= *(mv + 15);
	}
	GF128_xtime(mv);
	//4
	cv = (f >> 4) & 0x01;//f0,f1,...f7 1bit�� ����
	if (cv) {
		*(temp + 0) ^= *(mv + 0);
		*(temp + 1) ^= *(mv + 1);
		*(temp + 2) ^= *(mv + 2);
		*(temp + 3) ^= *(mv + 3);
		*(temp + 4) ^= *(mv + 4);
		*(temp + 5) ^= *(mv + 5);
		*(temp + 6) ^= *(mv + 6);
		*(temp + 7) ^= *(mv + 7);
		*(temp + 8) ^= *(mv + 8);
		*(temp + 9) ^= *(mv + 9);
		*(temp + 10) ^= *(mv + 10);
		*(temp + 11) ^= *(mv + 11);
		*(temp + 12) ^= *(mv + 12);
		*(temp + 13) ^= *(mv + 13);
		*(temp + 14) ^= *(mv + 14);
		*(temp + 15) ^= *(mv + 15);
	}
	GF128_xtime(mv);
	//3
	cv = (f >> 3) & 0x01;//f0,f1,...f7 1bit�� ����
	if (cv) {
		*(temp + 0) ^= *(mv + 0);
		*(temp + 1) ^= *(mv + 1);
		*(temp + 2) ^= *(mv + 2);
		*(temp + 3) ^= *(mv + 3);
		*(temp + 4) ^= *(mv + 4);
		*(temp + 5) ^= *(mv + 5);
		*(temp + 6) ^= *(mv + 6);
		*(temp + 7) ^= *(mv + 7);
		*(temp + 8) ^= *(mv + 8);
		*(temp + 9) ^= *(mv + 9);
		*(temp + 10) ^= *(mv + 10);
		*(temp + 11) ^= *(mv + 11);
		*(temp + 12) ^= *(mv + 12);
		*(temp + 13) ^= *(mv + 13);
		*(temp + 14) ^= *(mv + 14);
		*(temp + 15) ^= *(mv + 15);
	}
	GF128_xtime(mv);
	//2
	cv = (f >> 2) & 0x01;//f0,f1,...f7 1bit�� ����
	if (cv) {
		*(temp + 0) ^= *(mv + 0);
		*(temp + 1) ^= *(mv + 1);
		*(temp + 2) ^= *(mv + 2);
		*(temp + 3) ^= *(mv + 3);
		*(temp + 4) ^= *(mv + 4);
		*(temp + 5) ^= *(mv + 5);
		*(temp + 6) ^= *(mv + 6);
		*(temp + 7) ^= *(mv + 7);
		*(temp + 8) ^= *(mv + 8);
		*(temp + 9) ^= *(mv + 9);
		*(temp + 10) ^= *(mv + 10);
		*(temp + 11) ^= *(mv + 11);
		*(temp + 12) ^= *(mv + 12);
		*(temp + 13) ^= *(mv + 13);
		*(temp + 14) ^= *(mv + 14);
		*(temp + 15) ^= *(mv + 15);
	}
	GF128_xtime(mv);
	//1
	cv = (f >> 1) & 0x01;//f0,f1,...f7 1bit�� ����
	if (cv) {
		*(temp + 0) ^= *(mv + 0);
		*(temp + 1) ^= *(mv + 1);
		*(temp + 2) ^= *(mv + 2);
		*(temp + 3) ^= *(mv + 3);
		*(temp + 4) ^= *(mv + 4);
		*(temp + 5) ^= *(mv + 5);
		*(temp + 6) ^= *(mv + 6);
		*(temp + 7) ^= *(mv + 7);
		*(temp + 8) ^= *(mv + 8);
		*(temp + 9) ^= *(mv + 9);
		*(temp + 10) ^= *(mv + 10);
		*(temp + 11) ^= *(mv + 11);
		*(temp + 12) ^= *(mv + 12);
		*(temp + 13) ^= *(mv + 13);
		*(temp + 14) ^= *(mv + 14);
		*(temp + 15) ^= *(mv + 15);
	}
	GF128_xtime(mv);
	//0
	cv = (f >> 0) & 0x01;//f0,f1,...f7 1bit�� ����
	if (cv) {
		*(temp + 0) ^= *(mv + 0);
		*(temp + 1) ^= *(mv + 1);
		*(temp + 2) ^= *(mv + 2);
		*(temp + 3) ^= *(mv + 3);
		*(temp + 4) ^= *(mv + 4);
		*(temp + 5) ^= *(mv + 5);
		*(temp + 6) ^= *(mv + 6);
		*(temp + 7) ^= *(mv + 7);
		*(temp + 8) ^= *(mv + 8);
		*(temp + 9) ^= *(mv + 9);
		*(temp + 10) ^= *(mv + 10);
		*(temp + 11) ^= *(mv + 11);
		*(temp + 12) ^= *(mv + 12);
		*(temp + 13) ^= *(mv + 13);
		*(temp + 14) ^= *(mv + 14);
		*(temp + 15) ^= *(mv + 15);
	}
	GF128_xtime(mv);
	//temp -> f
	memcpy(result, temp, 16 * sizeof(byte));
}


//GHASH ���ȭ�� �ʿ��� TABLE ���� �Լ�
//KEY�� ���� HT1�� ��� �޶����� ��!
void gen_table1(byte* key) {
	//�־��� KEY�� ���� H�� ����
	byte H_IV[16] = { 0, };
	byte H[16];
	AES_ENC(H_IV, key, H);
	//in GF(2^128), (7�� ������ ���׽�)*H(x)�� ������� TABLE�� ����
	byte HT[256][16];
	byte result[16];
	int i, cnt_i, j;
	for (cnt_i = 0; cnt_i < 256; cnt_i++) {
		HT1_GF128_mul(cnt_i, H, result);
		memcpy(HT[cnt_i], result, 16 * sizeof(byte));
	}
	//���
	for (i = 0; i < 256; i++) {
		printf("{");
		for (j = 0; j < 16; j++) {
			if (j != 15)
				printf("0x%02x,", HT[i][j]);
			else
				printf("0x%02x", HT[i][j]);
		}
		printf("},");
		printf("\n");
	}
}