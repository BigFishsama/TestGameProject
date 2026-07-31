#pragma once
#include <graphics.h>
#include "Object.h"	
#include "fishsouptools.h"
#include "Tank.h"

class Bullet:public FishSoup_Object {
public:
	COLORREF color= RGB(94, 177, 94);
	double default_speed=2;
	double speed;
	double speedx, speedy;
	int default_siz=4;
	double siz;
	int extime = 800;

	

	static vector<pair<int, int> > pixels;
	
	virtual void render() override;
	Bullet(double x, double y, double speed, double r,double dis);
	~Bullet(){}
	virtual int update() override;
	virtual void update_model();
	virtual void update_speed();
	virtual void getHitbox(double tem_x, double tem_y, vector<pair<int, int>>& tem_pixels);
	virtual int checkHitbox(double tem_x, double tem_y);
};