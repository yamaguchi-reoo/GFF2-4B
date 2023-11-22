#include "Effect.h"
#include "GameMain.h"

Effect::Effect()
{
	//しぶきの発生位置(斬った敵の座標を持ってくる)
	location.x = 0;
	location.y = 0;

	//ゲージの座標
	gauge_x = 0;
	gauge_y = 0;
	
	//移動量
	v = 20;

	//発生個所からゲージまでの差
	diff_x = 0;
	diff_y = 0;

	//Flg(0:待機　1:移動中　2:ゲージに到達)
	Flg = 0;

}

Effect::~Effect()
{
}



void Effect::Update(GameMain* main)
{

	if (Flg == 1)
	{
		//しぶきの座標とゲージの座標の差
		diff_x = gauge_x - location.x;
		diff_y = gauge_y - location.y;

		//ゲージの中心より右の敵を倒したら
		if (gauge_x < location.x)
		{
			location.x -= fabsf(diff_x) / 20;
			location.y -= fabsf(diff_y) / v;
		}
		//ゲージの中心より左の敵を倒したら
		else if (gauge_x > location.x)
		{
			location.x += fabsf(diff_x) / 20;
			location.y -= fabsf(diff_y) / v;
		}


		if (location.y < (int)diff_y / 2)
		{
			v = 15;

			if (location.x < (int)diff_x / 3)
			{
				location.y -= 12;
			}
		}
	}

	if (Flg == 1 && gauge_x <= (int)location.x + 20 && gauge_x >= (int)location.x - 20 && gauge_y <= (int)location.y + 20 && gauge_y >= (int)location.y - 20)
	{
		Flg = 2;
		location.x = 0;
		location.y = 0;
	}
}



void Effect::Draw() const
{
	if (Flg == 1)
	{
		DrawCircle(location.x, location.y, 15, 0xffffff, TRUE);
	}

}


float Effect::SetLocation(Location _location)
{
	location.x = _location.x;
	location.y = _location.y;

	return location.x, location.y;
}

float Effect::SetGaugeLocation(Location _location)
{
	gauge_x = _location.x;
	gauge_y = _location.y;
	return gauge_x, gauge_y;
}

void Effect::SetSplashColor(ColorDate color)
{
	color_date.magenta = color.magenta;
	color_date.cyan = color.cyan;
	color_date.yellow = color.yellow;

}


