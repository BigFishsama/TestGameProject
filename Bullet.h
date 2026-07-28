#pragma once
#include <graphics.h>
#include "Object.h"	
#include "fishsouptools.h"
#include "Tank.h"

class Bullet:public FishSoup_Obeject {
public:
	double speed;
	// 出界修正值
	int d = 20;
	int siz = 5;
	virtual void render() override;
	Bullet(double x, double y, double speed, double r);
	~Bullet(){}
	virtual int update() override;
};