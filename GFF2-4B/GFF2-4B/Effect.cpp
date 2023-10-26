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
	
	//ゲージとしぶきの座標の差
	lenge_x = 0;
	lenge_y = 0;

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

}
