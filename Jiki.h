#define _USE_MATH_DEFINES  
#include <cmath>
#include <list>
#include <iostream>
#include "DxLib.h"
#define XINPUT_L_THUMB_DEADZONE 7849
#define XINPUT_R_THUMB_DEADZONE 8689
#define DEFAULT_MOVE_AMOUNT 3.5
#include "Shot.h"
#include "Laser.h"
#include "InputState.h"

using namespace std;

#ifndef _Jiki_H_
#define _Jiki_H_

class Jiki {
private:
	int handle;
	int x, y;
	double dx, dy;
	double moveamount;
	bool hitUpFlag, hitDownFlag, hitRightFlag, hitLeftFlag;
	list<Shot> shots;
	int shotHandle;
	double shotSpeed;
	Laser laser;
	InputState* inputState;
	list<Shot>::iterator itC, itD;
public:
	Jiki(int handle, InputState* inputState) :x(320), y(240), dx(320.0), dy(240.0), moveamount(5.0) {
		this->handle = handle;
		this->shotHandle = LoadGraph("nc95743.png");
		this->shotSpeed = 10.0;

		Laser laser(shotHandle, &x, &y, 10);
		this->laser = laser;

		this->inputState = inputState;
	}

	void calc() {
		calcPosition();
		beginShot();
		calcShots();
	}

	void calcPosition() {
		hitDownFlag = inputState->checkHitDown();
		hitUpFlag = inputState->checkHitUp();
		hitRightFlag = inputState->checkHitRight();
		hitLeftFlag = inputState->checkHitLeft();

		if ((hitDownFlag || hitUpFlag) && (hitRightFlag || hitLeftFlag)) {
			moveamount = DEFAULT_MOVE_AMOUNT * 0.7;
		}
		else {
			moveamount = DEFAULT_MOVE_AMOUNT;
		}

		if (inputState->checkHitLaserButton()) {
			moveamount = moveamount * 0.7;
		}

		if (hitRightFlag) {
			dx += moveamount;
		}
		if (hitLeftFlag) {
			dx -= moveamount;
		}
		if (hitDownFlag) {
			dy += moveamount;
		}
		if (hitUpFlag) {
			dy -= moveamount;
		}

		x = (int)dx;
		y = (int)dy;
	}

	void beginShot() {
		if (inputState->checkHitShotButton() && !inputState->checkHitLaserButton()) {
			Shot shotM(x, y, -M_PI / 2, shotSpeed, shotHandle);
			Shot shotL(x, y, -M_PI * 5 / 8, shotSpeed, shotHandle);
			Shot shotR(x, y, -M_PI * 3 / 8, shotSpeed, shotHandle);
			shots.push_front(shotM);
			shots.push_front(shotL);
			shots.push_front(shotR);
		}
	}

	void calcShots() {
		for (itC = shots.begin(); itC != shots.end(); ) {
			itC->calcPosition();
			if (!itC->checkInsideScreen()) {
				itC = shots.erase(itC);
				continue;
			}
			++itC;
		}
	}

	void draw() {
		drawShots();
		drawLaser();
		drawJiki();
	}

	void drawJiki() {
		DrawRotaGraph(x, y, 0.15, 0.0, handle, TRUE);
	}

	void drawShots() {
		for (itD = shots.begin(); itD != shots.end(); ++itD) {
			itD->drawShot();
		}
	}

	void drawLaser() {
		if (inputState->framesHoldLaserButton() >= 25) {
			laser.drawLaser(inputState->framesHoldLaserButton());
		}
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}

	list<Shot> getShots() {
		return shots;
	}
};

#endif