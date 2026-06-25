#pragma once

#include <graphics.h>
#include <cmath>

#define PI 3.14159265358979323846

inline double calcAngle(int x0, int y0,int tx,int ty)
{
	//细节颠倒，因为计算的是和y轴夹角
	return atan2(tx - x0,ty - y0);
}
inline void putPNGImage(int x, int y, IMAGE img)
{
    IMAGE img1;
    DWORD* d1;
    img1 = img;
    d1 = GetImageBuffer(&img1);

    float h, s, l;
    for (int i = 0; i < img1.getheight() * img1.getwidth(); i++)
    {
        RGBtoHSL(BGR(d1[i]), &h, &s, &l);
        if (l < 0.05)
        {
            d1[i] = BGR(WHITE);   // 低亮度->白色（掩码）
        }
        else
        {
            d1[i] = 0;            // 非白色->透明（黑色）
        }
    }
    putimage(x, y, &img1, SRCAND);
    putimage(x, y, &img, SRCPAINT);
}