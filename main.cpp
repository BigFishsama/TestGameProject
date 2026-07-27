#include <graphics.h>
#include <list>
#include "fishsouptools.h"
#include "Manager.h"

using namespace std;
const int FPS = 120;
const int perms = 1000 / FPS;
//int mx, my;

signed main()
{
	manager.init();
	BeginBatchDraw();
	while (1)
	{
		DWORD starttime = GetTickCount();
		//ExMessage mes;
		//while (peekmessage(&mes))
		//{
		//	mx = mes.x;
		//	my = mes.y;
		//}
		manager.update();
		cleardevice();
		manager.renderAllObeject();

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