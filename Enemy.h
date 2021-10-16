#define _USE_MATH_DEFINES  
#include <cmath>
#include <list>
#include <iostream>
#include "DxLib.h"
#define XINPUT_L_THUMB_DEADZONE 7849
#define XINPUT_R_THUMB_DEADZONE 8689

class Shot;

using namespace std;

#ifndef _Enemy_H_
#define _Enemy_H_

class Enemy {
private:
	int handle;
	int x, y;
	int timeSinceAppear;
	list<Shot> shots;
	int shotHandle;
	Jiki *jiki;
	list<Shot>::iterator itC, itD;
public:
	Enemy(int handle, int x, int y, int shotHandle, Jiki* jiki) :handle(handle), x(x), y(y), shotHandle(shotHandle), jiki(jiki) {
		timeSinceAppear = 0;
	}

	void calc() {
		timeSinceAppear = (++timeSinceAppear) % 100000;
		calcPosition();
		if (timeSinceAppear % 97 == 1) {
			beginShot();
		}
		calcShots();
	}
	void calcPosition() {
		x += 1;
	}
	void beginShot() {
		Shot shot(x, y, (double)(jiki->getX() - x), (double)(jiki->getY() - y), 2.0, shotHandle);
		shots.push_front(shot);
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
		drawEnemy();
	}
	void drawShots() {
		for (itD = shots.begin(); itD != shots.end(); ++itD) {
			itD->drawShot();
		}
	}
	void drawEnemy() {
		DrawRotaGraph(x, y, 0.1, 0.0, handle, TRUE);
	}

	bool checkInsideScreen() {
		if (0 <= x && x <= 640 && 0 <= y && y <= 480) {
			return true;
		}
		else {
			return false;
		}
	}
	bool checkShotsEmpty() {
		return shots.empty();
	}

	bool checkOut() {
		return (!checkInsideScreen()) && checkShotsEmpty();
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	list<Shot> getShots(){
		return shots;
	}
};

#endif