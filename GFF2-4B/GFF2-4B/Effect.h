#pragma once

#include "common.h"
#include "PadInput.h"

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
	float v; //�x�N�g��

public:
	Effect();
	~Effect();

	void Curve();

	void Update();
	void Draw()const;


};

