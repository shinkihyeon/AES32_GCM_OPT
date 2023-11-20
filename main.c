#include "main.h"

//GCM 운영모드를 이용해서 데이타을 AES32로 암호화한 결과값을
//출력해주는 함수
void GCM_printstate(byte* result, word size) {
	word cnt_i;
	printf("GCM_RESULT: ");
	printf("\n");
	for (cnt_i = 0; cnt_i < size; cnt_i++) {
		if (cnt_i != 0 && cnt_i % 16 == 0) {
			printf("\n");
		}
		printf("%02X ", result[cnt_i]);
	}
	printf("\n");
	printf("\n");
}


int main() {
	//GCM_TEST_VECTOR
	byte GCM_PT[16] = { 0Xc3,0Xb3,0Xc4,0X1f,0X11,0X3a,0X31,0Xb7,0X3d,0X9a,0X5c,0Xd4,0X32,0X10,0X30,0X69 };
	byte GCM_AAD[16] = { 0X24,0X82,0X56,0X02,0Xbd,0X12,0Xa9,0X84,0Xe0,0X09,0X2d,0X3e,0X44,0X8e,0Xda,0X5f };
	byte GCM_IV[16] = { 0Xb3,0Xd8,0Xcc,0X01,0X7c,0Xbb,0X89,0Xb3,0X9e,0X0f,0X67,0Xe2,0X00,0X00,0X00,0X01 };//Nonce||00..00..01
	byte GCM_KEY[16] = { 0Xc9,0X39,0Xcc,0X13,0X39,0X7c,0X1d,0X37,0Xde,0X6a,0Xe0,0Xe1,0Xcb,0X7c,0X42,0X3c };
	byte GCM_RESULT[32] = { 0, };

	//AES32를 GCM운영모드를 이용해서 16바이트 암호문과 16바이트 태그값이 CONCAT한 결과값 생성
	AES32_GCM_OPT(GCM_PT, 16, GCM_KEY, GCM_IV, GCM_AAD, 16, 16, GCM_RESULT);

	//CT||TAG 값 출력
	GCM_printstate(GCM_RESULT, 32);

	//아래 함수는 Master Key가 달라지면 HT1 값이 달라져야 해서 넣어놓음! 
	//즉, Master Key가 달라지면 아래 함수결과값으로 HT1 테이블 값 교체
	//gen_table1(GCM_KEY);
	
}


