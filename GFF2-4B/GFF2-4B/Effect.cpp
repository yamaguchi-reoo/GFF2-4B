#include "Effect.h"


Effect::Effect()
{
	//しぶきの発生位置(斬った敵の座標を持ってくる)
	splash.x = 800;
	splash.y = 500;
	splash.r = 15;

	splash.color_flg = 0x0000ff;

	//ゲージの座標
	gauge_x = 80;
	gauge_y = 80;
	
	//移動量
	v = 20;

	test_x = 0;
	test_y = 0;

}

Effect::~Effect()
{
}



void Effect::Update()
{

	//a = gauge_x - splash.x;
	//b = gauge_y - splash.y;
	//c = sqrt(a * a + b * b);



	//0を押したらしぶきが移動する
	if (CheckHitKey(KEY_INPUT_0) == true)
	{
		hit_flg = true;
	}

	if (hit_flg == true)
	{
		//しぶきの座標とゲージの座標の差
		test_x = gauge_x - splash.x;
		test_y = gauge_y - splash.y;

		splash.x -= fabs(test_x) / 50;

		if (splash.y < (int)test_y / 2)
		{
			v = -100;
		}
		splash.y -= fabs(test_y) / v;

	}

	if (splash.x <= 100)
	{
		hit_flg = false;
		splash.x = 800;
		splash.y = 500;
	}

}

void Effect::Draw() const
{

	DrawCircle(splash.x, splash.y, splash.r, splash.color_flg, TRUE);

	DrawLine(splash.x, splash.y, a, b, 0xff0000);
	DrawFormatString(600, 0, 0xffffff, "splash.x:%f", splash.x);
	DrawFormatString(600, 20, 0xffffff, "splash.y:%f", splash.y);
	DrawFormatString(600, 40, 0xffffff, "test x:%f", test_x);
	DrawFormatString(600, 60, 0xffffff, "test y:%f", test_y);
}
