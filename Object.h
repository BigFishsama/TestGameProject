#pragma once

#include <graphics.h>
#include "fishsouptools.h"
class FishSoup_Object
{
public:
	double x,y,r;
	virtual void render();
	virtual int update();
};