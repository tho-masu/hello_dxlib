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
	//ウィンドウモード変更と初期化と裏画面設定
	if (ChangeWindowMode(TRUE) != 0 || DxLib_Init() != 0) {
		return 0;
	}
	if (SetDrawScreen(DX_SCREEN_BACK) != 0) {
		DxLib_End();
		return 0;
	}

	InputState inputState;

	int handle = LoadGraph("自機.png");
	Jiki jiki(handle, &inputState);

	GameProcess gameProcess(&inputState, &jiki);

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && inputState.gpUpdateKey() == 0) {
		//計算部分
		gameProcess.calc();

		//描画部分
		gameProcess.draw();
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}