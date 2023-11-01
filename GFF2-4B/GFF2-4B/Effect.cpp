#include "Effect.h"


Effect::Effect()
{
	//しぶきの発生位置(斬った敵の座標を持ってくる)
	splash.x = 0;
	splash.y = 0;
	splash.r = 15;

	splash.color_flg = 0x000000;

	//ゲージの座標
	gauge_x = 80;
	gauge_y = 80;
	
	//移動量
	v = 20;

	test_x = 0;
	test_y = 0;

	end_flg = 0;

}

Effect::~Effect()
{
}



void Effect::Update()
{

	if (hit_flg == true)
	{
		//しぶきの座標とゲージの座標の差
		test_x = gauge_x - splash.x;
		test_y = gauge_y - splash.y;

		splash.x -= fabsf(test_x) / 50;
		splash.y -= fabsf(test_y) / v;
		
		end_flg = 1;

		if (splash.y < (int)test_y / 2)
		{
			v = 15;
		}
	}



	if (splash.x <= 100 && splash.y <= 100)
	{
		hit_flg = false;
		splash.x = 0;
		splash.y = 0;

		end_flg = 2;
	}
}



void Effect::Draw() const
{
	if (hit_flg == true)
	{
		DrawCircle(splash.x, splash.y, splash.r, splash.color_flg, TRUE);
	}

	DrawFormatString(500, 0, 0xff00ff, "end:%d", end_flg);
}



float Effect::SetLocation(Location location)
{
	splash.x = location.x;
	splash.y = location.y;

	return splash.x,splash.y;
}

int Effect::InitSplash()
{
	return end_flg;
}

