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

	//�����蔻��(0=�������Ă��Ȃ� 1=��ɓ������Ă��� 2=���ɓ������Ă��� 3=�E�ɓ������Ă��� 4=���ɓ������Ă���)
	int HitBox(BoxCollider* bCollider);

	//���S���W�̎擾
	Location GetLocation()const;

	//���a�̎擾
	Erea GetErea()const;

	//���S���W�̐ݒ�
	void SetLocation(Location location);
};