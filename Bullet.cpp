#include <graphics.h>
#include <algorithm>
#include "fishsouptools.h"
#include "Manager.h"
#include "Bullet.h"

vector<pair<int, int>> Bullet::pixels;

//r实际上没必要了
Bullet::Bullet(double x, double y, double speed, double r,double dis)
{
	this->speed = default_speed/scalelevel;
	this->r = r;
	this->siz = default_siz/scalelevel;
	pair<double, double> new_xy = calcMovePosition(x, y, r, dis+siz+1);
	this->x = new_xy.first;
	this->y = new_xy.second;
	update_model();
}
void Bullet::update_speed()
{
	speedx = speed * cos(r);
	speedy = speed * sin(r);
}

//暴力360度寻找, 1度为0.01745
void Bullet::getHitbox(double tem_x, double tem_y, vector<pair<int, int>>& tem_pixels)
{
	tem_pixels.clear();
	double tem_r = 0;
	for (int t = 0;t < 360;++t)
	{
		tem_pixels.emplace_back(calcMovePosition(0, 0, tem_r, siz));
		tem_r += 0.01745;
	}
	sort(tem_pixels.begin(), tem_pixels.end());
	auto tem_last = unique(tem_pixels.begin(), tem_pixels.end());
	tem_pixels.erase(tem_last, tem_pixels.end());
}
void Bullet::update_model()
{
	update_speed();
	getHitbox(0,0, pixels);
	//printf("Bullet speed: %.2lf, speedx: %.2lf,speedy: %.2lf\n", speed, speedx, speedy);
	//printf("pixel tot num: %d\n", pixels.size());
}
int Bullet::checkHitbox(double tem_x, double tem_y)
{
	getHitbox(tem_x, tem_y, pixels);
	int result = 1;
	for (auto i : pixels)
	{
		int x = (int)tem_x + i.first;
		int y = (int)tem_y + i.second;
		if (x < map_corner1_x || y < map_corner1_y || x>map_corner2_x || y>map_corner2_y)
		{
			//cout << map_corner1_x << ' ' << map_corner1_y << ' ' << map_corner2_x << ' ' << map_corner2_y << ' ';
			//cout << "x: " << x << "y: " << y << " ";
			return 0;
		}
		if (abs(map[x][y]) == time_tick)
		{
			return 2;
		}
		else if (map[x][y]==1)
		{
			result = 0;
		}
	}
	return result; //无视发生
}


int Bullet::update()
{
	if (--extime == 0)
	{
		return 0;
	}
	int check_result;

	check_result= checkHitbox(x + speedx, y);
	if (check_result == 0)
	{
		speedx = -speedx;
	}
	else 

	check_result = checkHitbox(x, y + speedy);
	if (check_result == 0)
	{
		speedy = -speedy;
	}
	
	x += speedx;
	y += speedy;
	check_result = checkHitbox(x, y);
	if (check_result==0)
	{
		cout << "Bomb by itself\n";
		return 0;
	}
	else if (check_result == 2)
	{
		cout << "The Bullet deleted due to Hit Player!\n";
		return 0;
	}
	//cout << "Bullet updated up on #" << time_tick << '\n';
	return 1;
}

void Bullet::render()
{
	setfillcolor(color);
	solidcircle(x, y, siz);
}

