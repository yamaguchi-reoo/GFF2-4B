#include "Effect.h"
#include "GameMain.h"

Effect::Effect()
{
	//���Ԃ��̔����ʒu(�a�����G�̍��W�������Ă���)
	splash.x = 0;
	splash.y = 0;
	splash.r = 15;

	//�Q�[�W�̍��W
	gauge_x = 80;
	gauge_y = 80;
	
	//�ړ���
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
		//���Ԃ��̍��W�ƃQ�[�W�̍��W�̍�
		test_x = gauge_x - splash.x;
		test_y = gauge_y - splash.y;

		//�Q�[�W�̒��S���E�̓G��|������
		if (gauge_x < splash.x)
		{
			splash.x -= fabsf(test_x) / 20;
			splash.y -= fabsf(test_y) / v;
		}
		//�Q�[�W�̒��S��荶�̓G��|������
		else if (gauge_x > splash.x)
		{
			splash.x += fabsf(test_x) / 20;
			splash.y -= fabsf(test_y) / v;
		}


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
		DrawCircle(splash.x, splash.y, splash.r,0x000000,  TRUE);
	}

	DrawFormatString(500, 0, 0xff00ff, "flg:%d", Flg);
}


float Effect::SetLocation(Location location)
{
	splash.x = location.x;
	splash.y = location.y;

	return splash.x,splash.y;
}

void Effect::SetSplashColor(ColorDate color)
{
	color_date.magenta = color.magenta;
	color_date.syan = color.syan;
	color_date.yellow = color.yellow;

}


