#define _USE_MATH_DEFINES  
#include <cmath>
#include <list>
#include <iostream>
#include "DxLib.h"
#define XINPUT_L_THUMB_DEADZONE 7849
#define XINPUT_R_THUMB_DEADZONE 8689
#include "Jiki.h"
#include "Enemy.h"
#include "InputState.h"

using namespace std;

#ifndef _GameProcess_H_
#define _GameProcess_H_

class GameProcess {
private:
	int timeSinceStart;
	Jiki* jiki;
	list<Enemy> enemies;
	InputState* inputState;
	int enemyHandle;
	int enemyShotHandle;
	list<Enemy>::iterator itC,itD;
	list<Shot>::iterator itS;
public:
	GameProcess(InputState* inputState, Jiki* jiki) {
		timeSinceStart = 0;
		this->inputState = inputState;
		this->jiki = jiki;
		this->enemyHandle = LoadGraph("ìG.png");
		this->enemyShotHandle = LoadGraph("nc95743.png");
	}

	void calc() {
		timeSinceStart = (++timeSinceStart) % 100000;
		jiki->calc();
		if (timeSinceStart % 200 == 1) {
			pushEnemy();
		}
		calcEnemies();
	}

	void pushEnemy() {
		Enemy enemy(enemyHandle,0,30,enemyShotHandle,jiki);
		enemies.push_front(enemy);
	}

	void calcEnemies() {
		for (itC = enemies.begin(); itC != enemies.end(); ) {
			itC->calc();
			//ìGÇ™âÊñ äOÇ…èoÇƒÇ¢ÇΩÇÁè¡ãé
			if (itC->checkOut()) {
				itC = enemies.erase(itC);
				continue;
			}
			//é©ã@ÇÃíeÇ…ìñÇΩÇ¡ÇƒÇ¢ÇΩÇÁè¡ãé
			list<Shot> shots = jiki->getShots();
			for (itS = shots.begin(); itS != shots.end(); ++itS) {
				int gapX = itS->getX() - itC->getX();
				int gapY = itS->getY() - itC->getY();
				if (gapX * gapX + gapY * gapY <= 400) {
					itC = enemies.erase(itC);
					goto CONTINUE_LABEL;
				}
			}

			++itC;

			CONTINUE_LABEL: {}
		}
	}

	void draw() {
		inputState->drawInput();
		jiki->draw();
		drawEnemies();
	}
	void drawEnemies() {
		for (itD = enemies.begin(); itD != enemies.end(); ++itD) {
			itD->draw();
		}
	}
};

#endif