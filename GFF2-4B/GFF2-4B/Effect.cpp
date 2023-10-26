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
	
	lenge_x = 0;
	lenge_y = 0;

	vx = 0;
	vy = 0;
}

Effect::~Effect()
{
}



void Effect::Update()
{
	
	if (CheckHitKey(KEY_INPUT_0) == true)
	{
		hit_flg = true;
	}

	if (hit_flg == TRUE)
	{
		lenge_x = gauge_x - splash.x;
		lenge_y = gauge_y - splash.y;

		vx = fabs(lenge_x)/20;
		vy = fabs(lenge_y)/20;

		splash.x -= vx;
		splash.y -= vy;

	}

}

void Effect::Draw() const
{

	DrawCircle(splash.x, splash.y, splash.r, splash.color_flg, TRUE);

	DrawFormatString(700, 0, 0x0000ff, "lenge_x:%f", fabs(lenge_x));
	DrawFormatString(700, 20, 0x0000ff, "lenge_y:%f", fabs(lenge_y));

	DrawFormatString(700, 40, 0x0000ff, "vx:%d", vx);
	DrawFormatString(700, 60, 0x0000ff, "vy:%d", vy);
}
