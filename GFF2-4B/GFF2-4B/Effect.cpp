#include "Effect.h"

Effect::Effect()
{
	//しぶきの発生位置(斬った敵の座標を持ってくる)
	splash.x = 800;
	splash.y = 500;
	splash.r = 15;

	splash.color_flg = 0x0000ff;

	//ゲージの座標
	gauge_x = 70;
	gauge_y = 80;
	
	//移動量
	vx = 0;
	vy = 0;
}

Effect::~Effect()
{
}



void Effect::Update()
{
	//0を押したらしぶきが移動する
	if (CheckHitKey(KEY_INPUT_0) == true)
	{
		hit_flg = true;
	}

	if (hit_flg == true)
	{
		float a = gauge_x - splash.x;
		float b = gauge_y - splash.y;
		float c = sqrtf(a * a + b * b);

		vx = c/100;
		vy = c/100;

		splash.x -= vx;
		splash.y -= vy;

	}

	if (splash.y < gauge_y)
	{
		hit_flg = false;
		splash.x = 800;
		splash.y = 500;
	}

}

void Effect::Draw() const
{

	DrawCircle(splash.x, splash.y, splash.r, splash.color_flg, TRUE);

}
