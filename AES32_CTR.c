#include "main.h"

//CTR운영모드에서 Counter값을 +1씩 증가시켜줘야 하는데
//그때 사용하는 함수
void CTR_INC(byte* ICTR) {
	int cnt_i;
	for (cnt_i = 15; cnt_i > 7; cnt_i--) {
		if (*(ICTR + cnt_i) != 0xff) {
			*(ICTR + cnt_i) += 1;
			break;
		}
		else {
			*(ICTR + cnt_i) = 0x00;
		}
	}
}

//AES-32bit + 운영모드:CTR
//아래 내용은 아래 코드에서 개선할점 제시
//동적할당 -> 속도저하 -> 미리 지역변수로 메모리를 크게 잡아서 필요한 부분만 사용
//해당 방식은 메모리는 비효율적이지만 속도는 상당히 효율적으로 빨라짐!
void AES32_CTR(byte* pt, byte* ct, byte* iv, word pt_len, byte* key) {
	byte ICTR[16] = { 0x00, };//Initial Counter 
	memcpy(ICTR, iv, 16 * sizeof(uint8_t));

	//카운터값 암호화 시킬 횟수
	//AES는 PT가 16바이트
	//암호화해야할 PT가 16의 배수 크기가 아닐때 
	//입력받은 PT의 DATA LENGTH에서 가장 가까운 16의 배수값을 찾는 과정
	//목적: Counter값을 AES32로 몇번을 암호화 시켜야 하는지를 알기 위해서
	word enc_len = (pt_len % 16 == 0) ? pt_len : pt_len + (16 - pt_len % 16);

	//카운터값 암호화한 값 들어가는 변수
	byte* temp = (uint8_t*)calloc(enc_len, sizeof(uint8_t));
	assert(temp != NULL);

	//CTR값을 AES32로 암호화
	uint32_t cnt_i;
	for (cnt_i = 0; cnt_i < enc_len / 16; cnt_i++) {
		AES_ENC(ICTR, key, temp + (cnt_i * 16));
		CTR_INC(ICTR);
	}

	//암호화된 Counter값과 PT와 XOR 해주는 과정
	for (cnt_i = 0; cnt_i < pt_len; cnt_i++) {
		*(ct + cnt_i) = *(pt + cnt_i) ^ *(temp + cnt_i);
	}

	//동적 메모리 해제
	free(temp);
	temp = NULL;
}