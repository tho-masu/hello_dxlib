#define _USE_MATH_DEFINES  
#include <cmath>
#include <list>
#include <iostream>
#include "DxLib.h"
#define XINPUT_L_THUMB_DEADZONE 7849
#define XINPUT_R_THUMB_DEADZONE 8689
#include "InputState.h"
#include "Jiki.h"
#include "GameProcess.h"
#include "Enemy.h"

using namespace std;

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	if (ChangeWindowMode(TRUE) != 0 || DxLib_Init() != 0) {
		return 0;
	}
	if (SetDrawScreen(DX_SCREEN_BACK) != 0) {
		DxLib_End();
		return 0;
	}

	InputState inputState;

	int handle = LoadGraph("���@.png");
	Jiki jiki(handle, &inputState);

	GameProcess gameProcess(&inputState, &jiki);

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && inputState.gpUpdateKey() == 0) {
		//�v�Z����
		gameProcess.calc();

		//�`�敔��
		gameProcess.draw();
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}