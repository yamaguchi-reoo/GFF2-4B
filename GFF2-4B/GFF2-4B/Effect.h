#pragma once
#include "common.h"
#include "PadInput.h"
#include "CharaBase.h"

#define _USE_MATH_DEFINES
#include <math.h>

//���Ԃ�
struct Splash
{
	float x, y;	//���S���W
	int r;	//���a

};

struct SplashColor
{
	float magenta;
	float syan;
	float yellow;
};

class Effect
{
private:

	Splash splash;	//�I�u�W�F�N�g��
	SplashColor s_color;

	bool hit_flg; //�e�X�g�p(true->�G�ɍU�������������Ƃ�)

	float v;

	float gauge_x, gauge_y;
	float test_x, test_y;

	float color_date;
	int Flg;

public:
	Effect();
	~Effect();

	void Update();
	void Draw()const;

	float SetLocation(Location location);

	int SetFlg(int flg)
	{
		Flg = flg;
		return Flg;
	}

	int GetFlg() { return Flg; }


};

