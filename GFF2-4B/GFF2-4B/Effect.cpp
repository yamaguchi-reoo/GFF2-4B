#include "Effect.h"

#include <math.h>

Effect::Effect()
{
	splash.x = 500;
	splash.y = 500;
	splash.r = 15;
	splash.color_flg = 0x00ffff;

	v = 5;
}

Effect::~Effect()
{
}

void Effect::Curve()
{

	splash.x -= v;
	splash.y -= v;
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

	if (splash.y == 85)
	{
		hit_flg = false;
	}
}

void Effect::Draw() const
{

	DrawCircle(splash.x, splash.y, splash.r, splash.color_flg, TRUE);
}
