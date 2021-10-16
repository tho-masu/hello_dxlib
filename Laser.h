#define _USE_MATH_DEFINES  
#include <cmath>
#include <list>
#include <iostream>
#include "DxLib.h"
#define XINPUT_L_THUMB_DEADZONE 7849
#define XINPUT_R_THUMB_DEADZONE 8689

using namespace std;

#ifndef _Laser_H_
#define _Laser_H_

class Laser {
private:
	int* x, * y;
	int px, py;
	int handle;
	int interval;
public:
	Laser() {}
	Laser(int handle, int* x, int* y, int interval) {
		this->handle = handle;
		this->x = x;
		this->y = y;
		this->interval = interval;
		px = 0;
		py = 0;
	}

	void drawLaser(int framesHoldLaserButton) {
		px = *x;
		py = *y - (framesHoldLaserButton % 3);
		while (py <= 480 && 0 <= py && 0 <= px && px <= 640) {
			DrawRotaGraph(px + ((py + framesHoldLaserButton) % 5 - 2), py, 0.07, 0.0, handle, TRUE);
			py -= interval;
		}
	}
};

#endif