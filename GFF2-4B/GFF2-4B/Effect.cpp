#include "Effect.h"
#include "GameMain.h"

Effect::Effect()
{
	//���Ԃ��̔����ʒu(�a�����G�̍��W�������Ă���)
	location.x = 0;
	location.y = 0;

	//�Q�[�W�̍��W
	gauge_x = 0;
	gauge_y = 0;
	
	//�ړ���
	v = 20;

	test_x = 0;
	test_y = 0;

	Flg = 0;

}

Effect::~Effect()
{
}



void Effect::Update(GameMain* main)
{

	if (Flg == 1)
	{
		//���Ԃ��̍��W�ƃQ�[�W�̍��W�̍�
		test_x = gauge_x - location.x;
		test_y = gauge_y - location.y;

		//�Q�[�W�̒��S���E�̓G��|������
		if (gauge_x < location.x)
		{
			location.x -= fabsf(test_x) / 20;
			location.y -= fabsf(test_y) / v;
		}
		//�Q�[�W�̒��S��荶�̓G��|������
		else if (gauge_x > location.x)
		{
			location.x += fabsf(test_x) / 20;
			location.y -= fabsf(test_y) / v;
		}


		if (location.y < (int)test_y / 2)
		{
			v = 15;

			if (location.x < (int)test_x / 3)
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


