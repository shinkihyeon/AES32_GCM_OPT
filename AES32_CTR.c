#include "main.h"

//CTR���忡�� Counter���� +1�� ����������� �ϴµ�
//�׶� ����ϴ� �Լ�
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

//AES-32bit + ����:CTR
//�Ʒ� ������ �Ʒ� �ڵ忡�� �������� ����
//�����Ҵ� -> �ӵ����� -> �̸� ���������� �޸𸮸� ũ�� ��Ƽ� �ʿ��� �κи� ���
//�ش� ����� �޸𸮴� ��ȿ���������� �ӵ��� ����� ȿ�������� ������!
void AES32_CTR(byte* pt, byte* ct, byte* iv, word pt_len, byte* key) {
	byte ICTR[16] = { 0x00, };//Initial Counter 
	memcpy(ICTR, iv, 16 * sizeof(uint8_t));

	//ī���Ͱ� ��ȣȭ ��ų Ƚ��
	//AES�� PT�� 16����Ʈ
	//��ȣȭ�ؾ��� PT�� 16�� ��� ũ�Ⱑ �ƴҶ� 
	//�Է¹��� PT�� DATA LENGTH���� ���� ����� 16�� ������� ã�� ����
	//����: Counter���� AES32�� ����� ��ȣȭ ���Ѿ� �ϴ����� �˱� ���ؼ�
	word enc_len = (pt_len % 16 == 0) ? pt_len : pt_len + (16 - pt_len % 16);

	//ī���Ͱ� ��ȣȭ�� �� ���� ����
	byte* temp = (uint8_t*)calloc(enc_len, sizeof(uint8_t));
	assert(temp != NULL);

	//CTR���� AES32�� ��ȣȭ
	uint32_t cnt_i;
	for (cnt_i = 0; cnt_i < enc_len / 16; cnt_i++) {
		AES_ENC(ICTR, key, temp + (cnt_i * 16));
		CTR_INC(ICTR);
	}

	//��ȣȭ�� Counter���� PT�� XOR ���ִ� ����
	for (cnt_i = 0; cnt_i < pt_len; cnt_i++) {
		*(ct + cnt_i) = *(pt + cnt_i) ^ *(temp + cnt_i);
	}

	//���� �޸� ����
	free(temp);
	temp = NULL;
}