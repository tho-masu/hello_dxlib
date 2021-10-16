#define _USE_MATH_DEFINES  
#include <cmath>
#include <list>
#include <iostream>
#include "DxLib.h"
#define XINPUT_L_THUMB_DEADZONE 7849
#define XINPUT_R_THUMB_DEADZONE 8689

using namespace std;

#ifndef _Xinput_H_
#define _Xinput_H_

struct Xinput {
	int Buttons[16];
	int LeftTrigger;
	int RightTrigger;
	int ThumbLX;
	int ThumbLY;
	int ThumbRX;
	int ThumbRY;
};

#endif

#ifndef _InputState_H_
#define _InputState_H_

class InputState {
private:
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��ꎞ�I�Ɋi�[����z��
	int key[256]; // �L�[��������Ă���t���[�������i�[����
	XINPUT_STATE tmpXinput; //xinput�̓��͏�Ԃ��ꎞ�I�Ɋi�[����\����
	Xinput xinput; //xinput�p�b�h�̓��͂���Ă���t���[�����i�X�e�B�b�N�̏ꍇ�͓��̗͂L���j���i�[����
	int Color; //�����F
public:
	InputState() {
		for (int i = 0; i < 256; ++i) {
			key[i] = 0;   // 0�ɂ���
		}
		for (int i = 0; i < 16; ++i) {
			xinput.Buttons[i] = 0;   // 0�ɂ���
		}
		xinput.LeftTrigger = 0;
		xinput.RightTrigger = 0;
		xinput.ThumbLX = 0;
		xinput.ThumbLY = 0;
		xinput.ThumbRX = 0;
		xinput.ThumbRY = 0;
		Color = GetColor(255, 255, 255);
	}

	// �L�[�̓��͏�Ԃ��X�V����
	int gpUpdateKey() {

		GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
		for (int i = 0; i < 256; ++i) {
			if (tmpKey[i] == 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă��Ȃ����
				key[i] = 0;   // 0�ɂ���
			}
			else {              // ������Ă�����
				++key[i];     // ���Z
			}
		}

		GetJoypadXInputState(DX_INPUT_PAD1, &tmpXinput); //���݂�xinput�̓��͏�Ԃ��擾����
		for (int i = 0; i < 16; ++i) {
			if (tmpXinput.Buttons[i] == 0) { // i�Ԃ̃R�[�h�ɑΉ�����{�^����������Ă��Ȃ��
				xinput.Buttons[i] = 0;   // 0�ɂ���
			}
			else {						// ������Ă�����
				++xinput.Buttons[i];     // ���Z
			}
		}
		//���g���K�[
		if (tmpXinput.LeftTrigger == 0) {
			xinput.LeftTrigger = 0;
		}
		else {
			++xinput.LeftTrigger;
		}
		//�E�g���K�[
		if (tmpXinput.RightTrigger == 0) {
			xinput.RightTrigger = 0;
		}
		else {
			++xinput.RightTrigger;
		}
		//���X�e�B�b�NX
		if (tmpXinput.ThumbLX > XINPUT_L_THUMB_DEADZONE) {
			xinput.ThumbLX = 1;
		}
		else if (tmpXinput.ThumbLX < -XINPUT_L_THUMB_DEADZONE) {
			xinput.ThumbLX = -1;
		}
		else {
			xinput.ThumbLX = 0;
		}
		//���X�e�B�b�NY
		if (tmpXinput.ThumbLY > XINPUT_L_THUMB_DEADZONE) {
			xinput.ThumbLY = 1;
		}
		else if (tmpXinput.ThumbLY < -XINPUT_L_THUMB_DEADZONE) {
			xinput.ThumbLY = -1;
		}
		else {
			xinput.ThumbLY = 0;
		}
		//�E�X�e�B�b�NX
		if (tmpXinput.ThumbRX > XINPUT_R_THUMB_DEADZONE) {
			xinput.ThumbRX = 1;
		}
		else if (tmpXinput.ThumbRX < -XINPUT_R_THUMB_DEADZONE) {
			xinput.ThumbRX = -1;
		}
		else {
			xinput.ThumbRX = 0;
		}
		//�E�X�e�B�b�NY
		if (tmpXinput.ThumbRY > XINPUT_R_THUMB_DEADZONE) {
			xinput.ThumbRY = 1;
		}
		else if (tmpXinput.ThumbRY < -XINPUT_R_THUMB_DEADZONE) {
			xinput.ThumbRY = -1;
		}
		else {
			xinput.ThumbRY = 0;
		}

		return 0;
	}

	bool checkHitRight() {
		if (key[KEY_INPUT_RIGHT] >= 1 || xinput.Buttons[XINPUT_BUTTON_DPAD_RIGHT] >= 1 || xinput.ThumbLX == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	bool checkHitLeft() {
		if (key[KEY_INPUT_LEFT] >= 1 || xinput.Buttons[XINPUT_BUTTON_DPAD_LEFT] >= 1 || xinput.ThumbLX == -1) {
			return true;
		}
		else {
			return false;
		}
	}

	bool checkHitUp() {
		if (key[KEY_INPUT_UP] >= 1 || xinput.Buttons[XINPUT_BUTTON_DPAD_UP] >= 1 || xinput.ThumbLY == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	bool checkHitDown() {
		if (key[KEY_INPUT_DOWN] >= 1 || xinput.Buttons[XINPUT_BUTTON_DPAD_DOWN] >= 1 || xinput.ThumbLY == -1) {
			return true;
		}
		else {
			return false;
		}
	}

	bool checkHitLaserButton() {
		if (xinput.Buttons[XINPUT_BUTTON_A] >= 1 || key[KEY_INPUT_LSHIFT] >= 1) {
			return true;
		}
		else {
			return false;
		}
	}

	int framesHoldLaserButton() {
		return max(xinput.Buttons[XINPUT_BUTTON_A], key[KEY_INPUT_LSHIFT]);
	}

	bool checkHitShotButton() {
		if (max(xinput.Buttons[XINPUT_BUTTON_LEFT_SHOULDER], key[KEY_INPUT_Z]) % 14 == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	void drawInput() {
		// ��ʂ� xinput �̒��g��`��
		DrawFormatString(0, 0, Color, "LeftTrigger:%d RightTrigger:%d",
			xinput.LeftTrigger, xinput.RightTrigger);
		DrawFormatString(0, 16, Color, "ThumbLX:%d ThumbLY:%d",
			xinput.ThumbLX, xinput.ThumbLY);
		DrawFormatString(0, 32, Color, "ThumbRX:%d ThumbRY:%d",
			xinput.ThumbRX, xinput.ThumbRY);
		DrawString(0, 64, "Button", Color);
		for (int i = 0; i < 16; ++i)
		{
			DrawFormatString(64 + i % 8 * 64, 64 + i / 8 * 16, Color,
				"%2d:%d", i, xinput.Buttons[i]);
		}
	}
};

#endif