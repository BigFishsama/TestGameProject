#pragma once
#include "Object.h"
#include <graphics.h>

class Ground :public FishSoup_Object
{
public:
	COLORREF color;
	int siz;
	virtual void render() override;
	Ground(double x, double y, int siz);
	Ground(double x, double y, COLORREF color);
	Ground(double x, double y, int siz,COLORREF color);
	~Ground(){}
};