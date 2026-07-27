#include <graphics.h>
#include "fishsouptools.h"
#include "Object.h"

void FishSoup_Obeject::render()
{
	rotateimage(&printed_Texture, &Texture, r, 0UL, 1);
	putPNGImage(x - printed_Texture.getwidth() / 2, y - printed_Texture.getheight() / 2, printed_Texture);
}

void FishSoup_Obeject::initrender()
{
	// 默认不做任何初始化
}

int FishSoup_Obeject::update()
{
	// 默认始终存在
	return 1;
}
