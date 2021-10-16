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
	char tmpKey[256]; // 現在のキーの入力状態を一時的に格納する配列
	int key[256]; // キーが押されているフレーム数を格納する
	XINPUT_STATE tmpXinput; //xinputの入力状態を一時的に格納する構造体
	Xinput xinput; //xinputパッドの入力されているフレーム数（スティックの場合は入力の有無）を格納する
	int Color; //文字色
public:
	InputState() {
		for (int i = 0; i < 256; ++i) {
			key[i] = 0;   // 0にする
		}
		for (int i = 0; i < 16; ++i) {
			xinput.Buttons[i] = 0;   // 0にする
		}
		xinput.LeftTrigger = 0;
		xinput.RightTrigger = 0;
		xinput.ThumbLX = 0;
		xinput.ThumbLY = 0;
		xinput.ThumbRX = 0;
		xinput.ThumbRY = 0;
		Color = GetColor(255, 255, 255);
	}

	// キーの入力状態を更新する
	int gpUpdateKey() {

		GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
		for (int i = 0; i < 256; ++i) {
			if (tmpKey[i] == 0) { // i番のキーコードに対応するキーが押されていなければ
				key[i] = 0;   // 0にする
			}
			else {              // 押されていたら
				++key[i];     // 加算
			}
		}

		GetJoypadXInputState(DX_INPUT_PAD1, &tmpXinput); //現在のxinputの入力状態を取得する
		for (int i = 0; i < 16; ++i) {
			if (tmpXinput.Buttons[i] == 0) { // i番のコードに対応するボタンが押されていなれば
				xinput.Buttons[i] = 0;   // 0にする
			}
			else {						// 押されていたら
				++xinput.Buttons[i];     // 加算
			}
		}
		//左トリガー
		if (tmpXinput.LeftTrigger == 0) {
			xinput.LeftTrigger = 0;
		}
		else {
			++xinput.LeftTrigger;
		}
		//右トリガー
		if (tmpXinput.RightTrigger == 0) {
			xinput.RightTrigger = 0;
		}
		else {
			++xinput.RightTrigger;
		}
		//左スティックX
		if (tmpXinput.ThumbLX > XINPUT_L_THUMB_DEADZONE) {
			xinput.ThumbLX = 1;
		}
		else if (tmpXinput.ThumbLX < -XINPUT_L_THUMB_DEADZONE) {
			xinput.ThumbLX = -1;
		}
		else {
			xinput.ThumbLX = 0;
		}
		//左スティックY
		if (tmpXinput.ThumbLY > XINPUT_L_THUMB_DEADZONE) {
			xinput.ThumbLY = 1;
		}
		else if (tmpXinput.ThumbLY < -XINPUT_L_THUMB_DEADZONE) {
			xinput.ThumbLY = -1;
		}
		else {
			xinput.ThumbLY = 0;
		}
		//右スティックX
		if (tmpXinput.ThumbRX > XINPUT_R_THUMB_DEADZONE) {
			xinput.ThumbRX = 1;
		}
		else if (tmpXinput.ThumbRX < -XINPUT_R_THUMB_DEADZONE) {
			xinput.ThumbRX = -1;
		}
		else {
			xinput.ThumbRX = 0;
		}
		//右スティックY
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
		// 画面に xinput の中身を描画
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