#include "Effect.h"

Effect::Effect()
{
	//���Ԃ��̔����ʒu(�a�����G�̍��W�������Ă���)
	splash.x = 800;
	splash.y = 500;
	splash.r = 15;

	splash.color_flg = 0x0000ff;

	//�Q�[�W�̍��W
	gauge_x = 70;
	gauge_y = 80;
	
	//�ړ���
	vx = 0;
	vy = 0;
}

Effect::~Effect()
{
}



void Effect::Update()
{
	//0���������炵�Ԃ����ړ�����
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
