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
	
	float vx,vy; //�x�N�g��
	int speed;	//�X�s�[�h
	float angle; //�p�x
	float timer; //�^�C�}�[
	float g;	//�d��

	float h, w;

public:
	Effect();
	~Effect();

	void Curve();

	void Update();
	void Draw()const;


};

