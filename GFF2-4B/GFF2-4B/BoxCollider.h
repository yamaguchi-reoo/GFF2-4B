#pragma once
#include "dxlib.h"
#include"common.h"

struct AttackData {
	float center_x;		//���S���W(x)
	float center_y;		//���S���W(y)
	float height;		//����
	float width;		//��
	bool who_attack;	//�N�̍U�����ifalse = ���� true = �G�j
	int attack_time;	//�ǂꂭ�炢���肪���̏�ɋ������邩
	bool direction;		//X���W����ɂ��Ăǂ̕����ɍU���𔭐������邩�̔��f(0=�E 1=��)
};
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