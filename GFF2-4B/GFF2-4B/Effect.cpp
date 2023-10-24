#include "Effect.h"



Effect::Effect()
{
	splash.x = 600;
	splash.y = 500;
	splash.r = 15;
	splash.color_flg = 0x00ffff;

	speed = 5;
	angle = 200;
	timer = 0.8;
	g = 0.98;

}

Effect::~Effect()
{
}

void Effect::Curve()
{
	float rad = angle * (float)M_PI / 180;
	vx = speed * sinf(rad) * timer;
	vy = speed * cosf(rad) * timer + (g * timer * timer)/ 2;
	splash.x = splash.x - vx;
	splash.y = splash.y - vy;
}

void Effect::Update()
{
	
	if (PadInput::OnButton(XINPUT_BUTTON_Y) == true)
	{
		hit_flg = true;
	}

	if (hit_flg == true)
	{
		Curve();
	}

	if (splash.y < 85)
	{
		hit_flg = false;
	}
}

void Effect::Draw() const
{

	DrawCircle(splash.x, splash.y, splash.r, splash.color_flg, TRUE);
}
