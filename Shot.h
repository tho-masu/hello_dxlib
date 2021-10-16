#define _USE_MATH_DEFINES  
#include <cmath>
#include <list>
#include <iostream>
#include "DxLib.h"
#define XINPUT_L_THUMB_DEADZONE 7849
#define XINPUT_R_THUMB_DEADZONE 8689

using namespace std;

#ifndef _Shot_H_
#define _Shot_H_

class Shot {
private:
	int x, y;
	double dx, dy;
	int handle;
	double angle, speed;
public:
	Shot(int x, int y, double angle, double speed, int handle) {
		this->x = x;
		this->y = y;
		this->dx = (double)x;
		this->dy = (double)y;
		this->angle = angle;
		this->speed = speed;
		this->handle = handle;
	}
	Shot(int x, int y, double vx, double vy, double speed, int handle) {
		this->x = x;
		this->y = y;
		this->dx = (double)x;
		this->dy = (double)y;
		this->angle = atan2(vy / sqrt(vx * vx + vy * vy), vx / sqrt(vx * vx + vy * vy));
		this->speed = speed;
		this->handle = handle;
	}

	void calcPosition() {
		dx += cos(angle) * speed;
		dy += sin(angle) * speed;
		x = (int)dx;
		y = (int)dy;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	void drawShot() {
		DrawRotaGraph(x, y, 0.05, angle + M_PI / 2, handle, TRUE);
		DrawFormatString(480, 0, GetColor(255, 255, 255), "x:%d, y:%d",
			x, y);
	}

	bool checkInsideScreen() {
		if (0 <= x && x <= 640 && 0 <= y && y <= 480) {
			return true;
		}
		else {
			return false;
		}
	}
};

#endif