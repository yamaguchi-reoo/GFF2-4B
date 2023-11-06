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
	int color_flg;	//�F��Flg

};

class Effect
{
private:

	Splash splash;	//�I�u�W�F�N�g��

	bool hit_flg; //�e�X�g�p(true->�G�ɍU�������������Ƃ�)

	float v;

	float gauge_x, gauge_y;
	float test_x, test_y;

	int end_flg;

public:
	Effect();
	~Effect();

	void Update();
	void Draw()const;

	bool HitFlg(bool hit)
	{
		hit_flg = hit;
		return hit_flg; 
	};

	float SetLocation(Location location);
	int InitSplash();

	int EndFlg(int end)
	{
		end_flg = end;
		return end_flg;
	};
};

