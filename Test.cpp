//#include <graphics.h>
//#include <iostream>
//#include <list>
//using namespace std;
//#define FPS 120
//double g;
//// 每帧变化g
//#define ybottom 500
//
//struct mycircle
//{
//	double x=400, y=0, r=50;
//	int R, G, B;
//	double v=0;
//}p;
//
//void move(mycircle& p)
//{
//	p.r -= 0.1;
//	p.v += g;
//	p.y += p.v;
//	if (p.y > ybottom - p.r)
//	{
//		p.y = ybottom - p.r;
//		p.v = -p.v;
//		p.v *= 0.8;
//	}
//	setfillcolor(RGB(p.R, p.G, p.B));
//}
//list<mycircle> l;
//signed main()
//{
//	srand((unsigned)time(0));
//	initgraph(800, 600);
//	p.R = 52, p.G = 152, p.B = 219;
//	setfillcolor(RGB(p.R, p.G, p.B));
//	double liney = ybottom, lenth = 0,lv=0,la=0.5;
//	bool isFinished = false;
//
//	int perms = 1000 / FPS;
//	g = 30.0 / FPS;
//
//	BeginBatchDraw();
//	while (1)
//	{
//		DWORD starttime = GetTickCount();
//		ExMessage mes;
//		while (peekmessage(&mes))
//		{
//			p.x = mes.x;
//			p.y = min(ybottom-p.r, mes.y);
//			if (mes.message == WM_LBUTTONUP)
//			{
//				l.push_back(p);
//				p.r = rand() % 70+30;
//				p.R = rand() % 256;
//				p.G = rand() % 256;
//				p.B = rand() % 256;
//			}
//		}
//		
//
//		if (!isFinished)
//		{
//			lv += la;
//			lenth += lv;
//			if (lenth > 400)
//			{
//				isFinished = 1;
//				lenth = 400;
//			}
//		}
//		cleardevice();
//		
//		for (auto it = l.begin();it != l.end();)
//		{
//			move(*it);
//			solidcircle((*it).x, (*it).y, (*it).r);
//			if ((*it).r <= 0)
//			{
//				it = l.erase(it);
//			}
//			else ++it;
//		}
//		setfillcolor(RGB(p.R, p.G, p.B));
//		solidcircle(p.x, p.y, p.r);
//
//		line(400-lenth, ybottom, 400+lenth, ybottom);
//
//		FlushBatchDraw();
//
//		DWORD duringtime = GetTickCount()-starttime;
//		if (duringtime <perms)
//		{
//			Sleep(perms- duringtime);
//		}
//	}
//	EndBatchDraw();
//	return 0;
//}