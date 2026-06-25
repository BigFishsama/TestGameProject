#include <graphics.h>
#include <list>
#include "fishsouptools.h"

using namespace std;
const int FPS = 120;
const int perms = 1000 / FPS;
int mx, my;
struct tank
{
	IMAGE tank,bullet;
	IMAGE print_tank,print_bullet;
	double x=400, y=300,r=0;
	int testsleep=0;
	void move(double dis)
	{
		double dy = dis * cos(r);
		double dx = dis * sin(r);
		x -= dx;
		y -= dy;
	}
	void turn(double radius)
	{
		r += PI / 180 * radius;
		rotateimage(&print_tank, &tank, r, 0UL, 1);
	}
	void printTank()
	{
		//putPNGImage(x, y, print_tank);
		putPNGImage(x-print_tank.getwidth()/2, y-print_tank.getheight()/2, print_tank);
	}
}player;
struct bullet
{
	tank* from;
	double x, y, r, speed;
	int d=20;//出界修正
	void printBullet()
	{
		rotateimage(&from->print_bullet, &from->bullet, r, 0UL, 1);
		putPNGImage(x - from->print_bullet.getwidth() / 2, y - from->print_bullet.getheight() / 2, from->print_bullet);
	}
	int yupdate()
	{
		double dx = speed * sin(r);
		double dy = speed * cos(r);
		
		x -= dx;
		y -= dy;
		if (x < 0 - d || y < 0 - d || x>800 + d || y>600 + d)
		{
			return 0;
		}
		return 1;
	}
	void initBullet(double x1, double y1, double speed1,double r1,tank* tank)
	{
		x = x1- speed1*10 * sin(r1);;
		y = y1- speed1*10 * cos(r1);
		speed = speed1;
		r = r1;
		from = tank;
	}
};
list<bullet> l;
void test1(tank* from)
{
	double x = (*from).x, y = (*from).y, r = (*from).r, speed = 5;
	bullet u1;
	u1.initBullet(x , y ,speed,r,from);
	l.push_back(u1);
}


void init()
{
	initgraph(800, 600);
	loadimage(&player.tank, L"image/Tanks/Tank.png",100,100,true);
	loadimage(&player.print_tank, L"image/Tanks/Tank.png", 100, 100, true);
	loadimage(&player.bullet, L"image/Bullets/bullet.png", 20, 34, true);
	loadimage(&player.print_bullet, L"image/Bullets/bullet.png", 20, 34, true);
}
signed main()
{
	init();
	BeginBatchDraw();
	while (1)
	{
		DWORD starttime = GetTickCount();
		ExMessage mes;
		while (peekmessage(&mes))
		{
			mx = mes.x;
			my = mes.y;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			player.turn(2);
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			player.turn(-2);
		}
		if(GetAsyncKeyState('W') & 0x8000)
		{
			player.move(3);
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			player.move(-3);
		}
		if (GetAsyncKeyState('R') & 0x8000)
		{
			if (player.testsleep == 0)
			{
				player.testsleep=40;
				test1(&player);
			}
		}
		if (player.testsleep) --player.testsleep;
		
		for (auto it = l.begin();it != l.end();)
		{
			int re=(*it).yupdate();
			if (re == 0)
			{
				it = l.erase(it);
				continue;
			}
			++it;
		}
		cleardevice();
		
		player.printTank();
		for (auto it = l.begin();it != l.end();++it)
		{
			(*it).printBullet();
		}

		FlushBatchDraw();//刷新到屏幕上
		DWORD duringtime = GetTickCount()-starttime;
		if (duringtime <perms)
		{
			Sleep(perms- duringtime);
		}
	}
	EndBatchDraw();
	return 0;
}