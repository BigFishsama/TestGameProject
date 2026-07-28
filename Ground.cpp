#include "Ground.h"
#include "fishsouptools.h"
#include <graphics.h>
using namespace std;
Ground::Ground(double x, double y,int siz)
{
	this->siz = siz;
	this->color = RGB(getRandomInt(0, 170), getRandomInt(0, 170), getRandomInt(0, 170));
	//if (getJudgement(25))
	//{
	//	this->color = RGB(172, 172, 172);
	//}
	//else this->color = 0xFFFFFF;
	this->x = x;
	this->y = y;
}
Ground::Ground(double x, double y, COLORREF color)
{
	this->siz = 50;
	this->x = x;
	this->y = y;
	this->color = color;
}
Ground::Ground(double x, double y, int siz, COLORREF color)
{
	this->x = x;
	this->y = y;
	this->siz = siz;
	this->color = color;
}
void Ground::render()
{
	setfillcolor(color);
	setlinecolor(color);
	fillrectangle(x, y, x + siz, y + siz);
}