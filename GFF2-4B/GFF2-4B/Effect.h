#pragma once
#include "common.h"
#include "PadInput.h"
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
	
	float lenge_x, lenge_y;

	float v;
	float t;
	float g;
	float angle;

	float gauge_x, gauge_y;
	float test_x, test_y;

	float a, b, c;

public:
	Effect();
	~Effect();

	void Update();
	void Draw()const;


};

