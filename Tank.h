#pragma once
#include <graphics.h>
#include <cmath>
#include "Object.h"

class Tank:public FishSoup_Obeject {
public:
	int cd_shoot = 100;
	
	char key_up, key_down, key_left, key_right, key_shoot;
	virtual void initrender() override;
	Tank(double x, double y, double r);
	Tank(double x, double y, double r, char key_up, char key_down, char key_left, char key_right, char key_shoot);
	virtual void move(double dis);
	virtual void turn(double radius);
	virtual void shoot();
	virtual int update() override;
};