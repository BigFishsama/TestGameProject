#pragma once

#include <graphics.h>
#include "fishsouptools.h"
class FishSoup_Obeject
{
public:
	//基础贴图，以及经过调整后的贴图
	IMAGE Texture,printed_Texture;
	double x,y,r;
	virtual void initrender();
	virtual void render();
	virtual int update();
};