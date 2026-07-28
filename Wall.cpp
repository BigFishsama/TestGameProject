#include "Wall.h"
#include "Manager.h"
using namespace std;

Wall::Wall(double x, double y, int style,double weight)
{
	this->x = x;
	this->y = y;
	this->weight = weight;
	this->style = style;
	update_model();
}
void Wall::update_model()
{
	this->d = default_d / scalelevel;
}
void Wall::render()
{
	setfillcolor(color);
	setlinecolor(color);
	if (style<2)
	{
		fillrectangle(x-d, y-d, x +2*d+weight, y +2*d);
	}
	else
	{
		fillrectangle(x - d, y - d, x + 2 * d , y + 2 * d + weight);
	}
}