#include <graphics.h>
#include <iostream>
#include "Tank.h"
#include "Bullet.h"
#include "fishsouptools.h"
#include "Manager.h"

Tank::Tank(double x,double y,double r)
{
	this->x = x;
	this->y = y;
	this->r = r;
	update_model();
}
Tank::Tank(double x, double y, double r,int controlmode)
{
	this->controlmode = controlmode;
	Tank(x, y, r);
}
void Tank::update_model()
{
	//日志
	cout << "model has been updated successfully!\n";
	cout << "The scalelevel is " << scalelevel<<'\n';

	height = default_height / scalelevel;
	weight = default_weight / scalelevel;
	body_left_height = default_body_left_height / scalelevel;
	body_left_weight = default_body_left_weight / scalelevel;
	body_right_height = default_body_right_height / scalelevel;
	body_right_weight = default_body_right_weight / scalelevel;

	back_left_height = default_back_left_height / scalelevel;
	back_left_weight = default_back_left_weight / scalelevel;
	back_right_height = default_back_right_height / scalelevel;
	back_right_weight = default_back_right_weight / scalelevel;

	turret_left_height = default_turret_left_height / scalelevel;
	turret_left_weight = default_turret_left_weight / scalelevel;
	turret_right_height = default_turret_right_height / scalelevel;
	turret_right_weight = default_turret_right_weight / scalelevel;

	barrel_left_height = default_barrel_left_height / scalelevel;
	barrel_left_weight = default_barrel_left_weight / scalelevel;
	barrel_right_height = default_barrel_right_height / scalelevel;
	barrel_right_weight = default_barrel_right_weight / scalelevel;

	d_height = default_d_height / scalelevel;
	d_weight = default_d_weight / scalelevel;

	this->movespeed = default_movespeed / scalelevel;
	this->turnspeed = default_turnspeed;
	base_length = (double)sqrt((height / 2.0) * (height / 2.0) + (weight / 2.0) * (weight / 2.0));

	//底座四个点从左上角顺时针到左下角
	r1 = atan2(-height, -weight);
	r2 = atan2(-height, weight);
	r3 = atan2(height, weight);
	r4 = atan2(height, -weight);

	//得到车身四个点
	body_length1= (double)sqrt(body_left_height * body_left_height +body_left_weight * body_left_weight);
	r5 = atan2(-body_left_height, -body_left_weight);

	body_length2 = (double)sqrt(body_right_height * body_right_height  + body_right_weight * body_right_weight );
	r6 = atan2(-body_right_height, body_right_weight);
	
	body_length3 = (double)sqrt(body_right_height * body_right_height +body_right_weight* body_right_weight);
	r7 = atan2(body_right_height, body_right_weight);

	body_length4 = (double)sqrt(body_left_height * body_left_height  +body_left_weight  * body_left_weight );
	r8 = atan2(body_left_height, -body_left_weight);

	//后侧
	back_length1 = (double)sqrt(back_left_height * back_left_height + back_left_weight * back_left_weight);
	r9 = atan2(-back_left_height, -back_left_weight);

	back_length2 = (double)sqrt(back_right_height * back_right_height + back_right_weight * back_right_weight);
	r10 = atan2(-back_right_height, -back_right_weight);

	back_length3 = (double)sqrt(back_right_height * back_right_height + back_right_weight * back_right_weight);
	r11 = atan2(back_right_height, -back_right_weight);

	back_length4 = (double)sqrt(back_left_height * back_left_height + back_left_weight * back_left_weight);
	r12 = atan2(back_left_height, -back_left_weight);

	//炮台
	turret_length1 = (double)sqrt(turret_left_height * turret_left_height + turret_left_weight * turret_left_weight);
	r13 = atan2(-turret_left_height, -turret_left_weight);

	turret_length2 = (double)sqrt(turret_right_height * turret_right_height + turret_right_weight * turret_right_weight);
	r14 = atan2(-turret_right_height, turret_right_weight);

	turret_length3 = (double)sqrt(turret_right_height * turret_right_height + turret_right_weight * turret_right_weight);
	r15 = atan2(turret_right_height, turret_right_weight);

	turret_length4 = (double)sqrt(turret_left_height * turret_left_height + turret_left_weight * turret_left_weight);
	r16 = atan2(turret_left_height, -turret_left_weight);

	//炮筒
	barrel_length1 = (double)sqrt(barrel_left_height * barrel_left_height + barrel_left_weight * barrel_left_weight);
	r17 = atan2(-barrel_left_height, -barrel_left_weight);

	barrel_length2 = (double)sqrt(barrel_right_height * barrel_right_height + barrel_right_weight * barrel_right_weight);
	r18 = atan2(-barrel_right_height, barrel_right_weight);

	barrel_length3 = (double)sqrt(barrel_right_height * barrel_right_height + barrel_right_weight * barrel_right_weight);
	r19 = atan2(barrel_right_height, barrel_right_weight);

	barrel_length4 = (double)sqrt(barrel_left_height * barrel_left_height + barrel_left_weight * barrel_left_weight);
	r20 = atan2(barrel_left_height, -barrel_left_weight);

	//碰撞箱
	d_length1 = (double)sqrt(d_height * d_height + d_weight * d_weight);
	r21 = atan2(-d_height, d_weight);

	d_length2 = (double)sqrt(d_height * d_height + d_weight * d_weight);
	r22 = atan2(d_height, d_weight);

	//加载一次碰撞箱
	getHitbox(x,y,r,hitbox);
}

// 向方向上移动dis个单位长度
void Tank::move(double dis)
{
	//调用工具函数，返回新位置
	pair<double, double> new_xy = calcMovePosition(this->x, this->y, this->r, dis);
	if (checkHitbox(new_xy.first, y, this->r))
	{
		this->x = new_xy.first;
	}
	if (checkHitbox(x,new_xy.second, this->r))
	{
		this->y = new_xy.second;
	}
	//else cout << "DEBUG#1: Fail to MOVE due to Hitbox\n";
}


// 旋转radius弧度，顺时针方向为正，0度是x轴向右
//1°约为0.01745
void Tank::turn(double radius)
{
	double tem_r = this->r + radius * 0.01745;
	if (checkHitbox(this->x, this->y, tem_r))
	{
		this->r = tem_r;
	}
	//else cout << "DEBUG#2: Fail to TURN due to Hitbox\n";
}

// 发射子弹
void Tank::shoot()
{
	double x = this->x, y = this->y, r = this->r, speed = 5;
	Bullet* tem_Bullet=new Bullet(x, y, speed,r, barrel_right_weight);

	render_list.push_back(tem_Bullet);
}

// 处理按键信息
int Tank::update()
{
	//cout <<"Tank has been updated successfully !!!";
	int input_move=0, input_turn = 0;
	bool input_shoot = false;
	if (controlmode == 1)
	{
		if (GetAsyncKeyState('A') & 0x8000) input_turn -= 1;
		if (GetAsyncKeyState('D') & 0x8000) input_turn += 1;
		if (GetAsyncKeyState('W') & 0x8000) input_move += 1;
		if (GetAsyncKeyState('S') & 0x8000) input_move -= 1;
		if (GetAsyncKeyState('R') & 0x8000)
		{
			if (this->cd_shoot == 0)
			{
				input_shoot = 1;
			}
		}
	}
	else
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) input_turn -= 1;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) input_turn += 1;
		if (GetAsyncKeyState(VK_UP) & 0x8000) input_move += 1;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) input_move -= 1;
		if (GetAsyncKeyState('P') & 0x8000)
		{
			if (this->cd_shoot == 0)
			{
				input_shoot = 1;
			}
		}
	}
	if (input_move != 0)
	{
		this->move(movespeed * input_move);
		//if (!checkHitbox(x, y, r))
		//{
		//	cout << "CRASH#3 HitBox Error.Moving!\n";
		//}
	}
	if (input_turn != 0)
	{
		this->turn(turnspeed * input_turn);
		//if (!checkHitbox(x, y, r))
		//{
		//	cout << "CRASH#4 HitBox Error.Turing!\n";
		//}
	}
	if (input_shoot)
	{
		this->cd_shoot = 41;
		this->shoot();
	}
	if (this->cd_shoot) --this->cd_shoot;
	//玩家永远不出界，不删除，返回1

	update_hitbox();
	//cout << "Tank updated up on #" << time_tick << '\n';
	return 1;
}

void Tank::getHitbox(double tem_x, double tem_y, double tem_r, vector<pair<int, int>>& tem_pixels)
{
	//加一层保险
	tem_pixels.clear();

	pair<int, int> point1, point2, point3, point4, point5, point6, point7,point8;
	point1 = calcMovePosition(tem_x, tem_y, r1 + tem_r, base_length);
	point2 = calcMovePosition(tem_x, tem_y, r2 + tem_r, base_length);
	point3 = calcMovePosition(tem_x, tem_y, r21 + tem_r, d_length1);
	point4 = calcMovePosition(tem_x, tem_y, r22 + tem_r, d_length2);

	point5 = calcMovePosition(tem_x, tem_y, r18 + tem_r, barrel_length2);
	point6 = calcMovePosition(tem_x, tem_y, r19 + tem_r, barrel_length3);
	
	point7 = calcMovePosition(tem_x, tem_y, r3 + tem_r, base_length);
	point8 = calcMovePosition(tem_x, tem_y, r4 + tem_r, base_length);

	getLinepixel(point1.first, point1.second, point2.first, point2.second,tem_pixels);
	getLinepixel(point2.first, point2.second, point3.first, point3.second, tem_pixels);
	getLinepixel(point3.first, point3.second, point4.first, point4.second, tem_pixels);
	getLinepixel(point4.first, point4.second, point5.first, point5.second, tem_pixels);
	getLinepixel(point5.first, point5.second, point6.first, point6.second, tem_pixels);
	getLinepixel(point6.first, point6.second, point7.first, point7.second, tem_pixels);
	getLinepixel(point7.first, point7.second, point8.first, point8.second, tem_pixels);
	getLinepixel(point8.first, point8.second, point1.first, point1.second, tem_pixels);
}
bool Tank::checkHitbox(double tem_x, double tem_y, double tem_r)
{
	vector<pair<int, int> > tem_pixels;
	getHitbox(tem_x, tem_y, tem_r, tem_pixels);

	//DEBUG
	//debug(tem_pixels.size())
	for (auto i : tem_pixels)
	{
		//cout << i.first << ' ' << i.second << '\n';
		if (map[(int)i.first][(int)i.second]==1)
		{
			//cout << "Find!";
			return false;
		}
	}
	return true;
}

void Tank::render()
{
	//绘制底座
	POINT tem_points1[] = { {point1.first,point1.second},{point2.first,point2.second} ,{point3.first,point3.second},{point4.first,point4.second} };
	drawrectangle(tem_points1,track_outline_color,track_color);

	POINT tem_points2[] = { {point5.first,point5.second},{point6.first,point6.second} ,{point7.first,point7.second},{point8.first,point8.second} };
	setfillcolor(body_color);
	solidpolygon(tem_points2, 4);

	POINT tem_points3[]= { {point9.first,point9.second},{point10.first,point10.second} ,{point11.first,point11.second},{point12.first,point12.second} };
	setfillcolor(back_color);
	solidpolygon(tem_points3, 4);

	POINT tem_points4[] = { {point13.first,point13.second},{point14.first,point14.second} ,{point15.first,point15.second},{point16.first,point16.second} };
	setfillcolor(turret_color);
	solidpolygon(tem_points4, 4);

	POINT tem_points5[] = { {point17.first,point17.second},{point18.first,point18.second} ,{point19.first,point19.second},{point20.first,point20.second} };
	drawrectangle(tem_points5, barrel_outline_color, barrel_color);
}

void Tank::update_hitbox()
{
	getHitbox(x, y, r, hitbox);
	for (auto i : hitbox)
	{
		if (controlmode == 1) map[i.first][i.second] = time_tick;
		else map[i.first][i.second] = -time_tick;
	}
	point1 = calcMovePosition(x, y, r1 + r, base_length);
	point2 = calcMovePosition(x, y, r2 + r, base_length);
	point3 = calcMovePosition(x, y, r3 + r, base_length);
	point4 = calcMovePosition(x, y, r4 + r, base_length);
	
	point5 = calcMovePosition(x, y, r5 + r, body_length1);
	point6 = calcMovePosition(x, y, r6 + r, body_length2);
	point7 = calcMovePosition(x, y, r7 + r, body_length3);
	point8 = calcMovePosition(x, y, r8 + r, body_length4);

	point9 = calcMovePosition(x, y, r9 + r, back_length1);
	point10 = calcMovePosition(x, y, r10 + r, back_length2);
	point11 = calcMovePosition(x, y, r11 + r, back_length3);
	point12 = calcMovePosition(x, y, r12 + r, back_length4);

	point13 = calcMovePosition(x, y, r13 + r, turret_length1);
	point14 = calcMovePosition(x, y, r14 + r, turret_length2);
	point15 = calcMovePosition(x, y, r15 + r, turret_length3);
	point16 = calcMovePosition(x, y, r16 + r, turret_length4);

	point17 = calcMovePosition(x, y, r17 + r, barrel_length1);
	point18 = calcMovePosition(x, y, r18 + r, barrel_length2);
	point19 = calcMovePosition(x, y, r19 + r, barrel_length3);
	point20 = calcMovePosition(x, y, r20 + r, barrel_length4);
}