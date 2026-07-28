#pragma once
#include <graphics.h>
//pair头文件
#include <utility>
#include <cmath>
#include <random>

#define PI 3.14159265358979323846
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