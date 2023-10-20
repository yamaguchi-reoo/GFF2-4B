#pragma once
#include "dxlib.h"
#include"common.h"

//���S���W
struct Location
{
	float x;	//������W(x)
	float y;	//������W(y)
};

//�͈�
struct Erea
{
	float height;	//����
	float width;	//��
};

class BoxCollider
{
protected:
	Location location;	//���S���W
	Erea erea; //�͈�
public:

	//�����蔻�� (0,0 = �������Ă��Ȃ� ����ȊO = ����̒��S���W)
	bool HitBox(BoxCollider* bCollider);

	//������W�̎擾
	Location GetLocation()const;

	//���S���W�̎擾
	Location GetCenterLocation()const;

	//���a�̎擾
	Erea GetErea()const;
};