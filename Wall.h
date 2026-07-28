#pragma once
#include "Object.h"
class Wall :public FishSoup_Object
{
public:
	double weight;
	int style;

	//突出长度
	double default_d = 2;
	double d;

	COLORREF color=RGB(128, 128, 128);

	Wall(double x, double y, int style,double weight);
	virtual void render() override;
	virtual void update_model();
};