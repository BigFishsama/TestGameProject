#pragma once
#include <graphics.h>
//pair头文件
#include <utility>
#include <iostream>
#include <cmath>
#include <random>

#define PI 3.14159265358979323846
#define debug(x) cout<<#x<<":"<<x<<'\n';
using namespace std;

//所有的方法都要内联，防止重复定义
inline pair<double, double> calcMovePosition(double x,double y,double r,double dis)
{
    double dy = dis * sin(r);
    double dx = dis * cos(r);
    x += dx;
    y += dy;
    return { x,y };
}

inline mt19937& getRandomEngine()
{
    //创建一个全局的随机数序列
    //事实上，这个是个状态机，不能看成普通的变量或数组，它每次调用后会自动更新为下一个数字
    //{}初始化空序列，()是调用重载的生成方法
    static mt19937 engine(random_device{}());
    return engine;
}

//获取一个范围在 [minn,maxn] 的整随机数
inline int getRandomInt(int minn,int maxn)
{
    uniform_int_distribution<int> dist(minn, maxn);
    return dist(getRandomEngine());
}

//发生概率为 pd% 的事件，进行一次真假随机判断，若为真返回1
inline bool getJudgement(int pd)
{
    return getRandomInt(0, 100) <= pd ? 1 : 0;
}

//画有边框矩形
inline void drawrectangle(POINT* tem_points,COLORREF outline_color,COLORREF fill_color)
{
    setfillcolor(fill_color);
    solidpolygon(tem_points, 4);

    setlinecolor(outline_color);
    line(tem_points[0].x, tem_points[0].y, tem_points[1].x, tem_points[1].y);
    line(tem_points[1].x, tem_points[1].y, tem_points[2].x, tem_points[2].y);
    line(tem_points[2].x, tem_points[2].y, tem_points[3].x, tem_points[3].y);
    line(tem_points[3].x, tem_points[3].y, tem_points[0].x, tem_points[0].y);
}

//获取偏水平直线像素点
inline void getLineXpixel(int tem_x1, int tem_y1, int tem_x2, int tem_y2, vector<pair<int, int>>& tem_pixels)
{
    if (tem_x1 > tem_x2)
    {
        swap(tem_x1, tem_x2);
        swap(tem_y1, tem_y2);
    }
    int dx = tem_x2 - tem_x1, dy = tem_y2 - tem_y1;
    int dir = dy > 0 ? 1 : -1;
    dy *= dir;
    if (dx != 0)
    {
        int y = tem_y1;
        int p = 2 * dy - dx;
        for (int t = 0;t <= dx;++t)
        {
            tem_pixels.emplace_back(tem_x1 + t,y);
            if (p >= 0)
            {
                y += dir;
                p -= 2 * dx;
            }
            p += 2 * dy;
        }
    }
}
//获取偏垂直直线像素点
inline void getLineYpixel(int tem_x1, int tem_y1, int tem_x2, int tem_y2, vector<pair<int, int>>& tem_pixels)
{
    if (tem_y1 > tem_y2)
    {
        swap(tem_x1, tem_x2);
        swap(tem_y1, tem_y2);
    }
    int dx = tem_x2 - tem_x1, dy = tem_y2 - tem_y1;
    int dir = dx > 0 ? 1 : -1;
    dx *= dir;
    if (dy != 0)
    {
        int x = tem_x1;
        int p = 2 * dx - dy;
        for (int t = 0;t <= dy;++t)
        {
            tem_pixels.emplace_back(x,tem_y1+t);
            if (p >= 0)
            {
                x += dir;
                p -= 2 * dy;
            }
            p += 2 * dx;
        }
    }
}

//获取一条粗度为1的线上的所有像素点位置
inline void getLinepixel(int tem_x1, int tem_y1, int tem_x2, int tem_y2, vector<pair<int, int>>& tem_pixels)
{
    if (abs(tem_x2 - tem_x1) > abs(tem_y2 - tem_y1))
    {
        getLineXpixel(tem_x1, tem_y1, tem_x2, tem_y2, tem_pixels);
    }
    else
    {
        getLineYpixel(tem_x1, tem_y1, tem_x2, tem_y2, tem_pixels);
    }
}


// atan2(y,x)，假设物体位于0，0，初始面向右方向，想要转到(x,y)这个点
// 返回的是以essayX坐标轴x轴为0度，顺时针需要转的角度
// 比如atan2(-1,-1)返回-135度，需要逆时针转135度，正确
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