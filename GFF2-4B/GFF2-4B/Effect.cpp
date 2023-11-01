#include "Effect.h"


Effect::Effect()
{
	//しぶきの発生位置(斬った敵の座標を持ってくる)
	splash.x = 0;
	splash.y = 0;
	splash.r = 15;

	color_date = 0xffffff;

	//ゲージの座標
	gauge_x = 80;
	gauge_y = 80;
	
	//移動量
	v = 20;

	test_x = 0;
	test_y = 0;

	Flg = 0;

}

Effect::~Effect()
{
}



void Effect::Update()
{

	if (Flg == 1)
	{
		//しぶきの座標とゲージの座標の差
		test_x = gauge_x - splash.x;
		test_y = gauge_y - splash.y;

		splash.x -= fabsf(test_x) / 20;
		splash.y -= fabsf(test_y) / v;

		if (splash.y < (int)test_y / 2)
		{
			v = 15;
		}
	}



	if (Flg == 1 && gauge_x == (int)splash.x && gauge_y == (int)splash.y)
	{
		Flg = 2;
		splash.x = 0;
		splash.y = 0;
	}


}



void Effect::Draw() const
{
	if (Flg == 1)
	{
		DrawCircle(splash.x, splash.y, splash.r, color_date, TRUE);
	}

	DrawFormatString(500, 0, 0xff00ff, "flg:%d", Flg);
}



float Effect::SetLocation(Location location)
{
	splash.x = location.x;
	splash.y = location.y;

	return splash.x,splash.y;
}




