#pragma once
#include "dxlib.h"
#include"common.h"

struct AttackData {
	float x;			//������W(x)
	float y;			//������W(y)
	float height;		//����
	float width;		//��
	int who_attack;		//�N�̍U����(who�ƍ��킹�Ďg��)
	int attack_time;	//�ǂꂭ�炢���肪���̏�ɋ������邩
	bool direction;		//X���W����ɂ��Ăǂ̕����ɍU���𔭐������邩�̔��f(0=�E 1=��)
	int damage;			//�^����_���[�W��
	int delay;			//���t���[���҂��Ă���U�����邩
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
	int who;	//�v���C���[���G���A�G�Ȃ�ǂ̎�ނ̉��̖ڂ���ۑ�����
public:

	//�����蔻�� (0,0 = �������Ă��Ȃ� ����ȊO = ����̒��S���W)
	bool HitBox(BoxCollider* bCollider);

	//������W�̎擾
	Location GetLocation()const;

	//���S���W�̎擾
	Location GetCenterLocation()const;

	//���a�̎擾
	Erea GetErea()const;

	//�v���C���[���G���A�G�Ȃ�ǂ̎�ނ̉��̖ڂ����擾����
	int GetWho() { return who; }
};