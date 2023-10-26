#include "Effect.h"

Effect::Effect()
{
	//���Ԃ��̔����ʒu(�a�����G�̍��W�������Ă���)
	splash.x = 200;
	splash.y = 500;
	splash.r = 15;

	splash.color_flg = 0x00ffff;

	//�Q�[�W�̍��W
	gauge_x = 80;
	gauge_y = 70;
	
	lenge_x = 0;
	lenge_y = 0;
}

Effect::~Effect()
{
}



void Effect::Update()
{
	
	if (PadInput::OnButton(XINPUT_BUTTON_Y) == true)
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
