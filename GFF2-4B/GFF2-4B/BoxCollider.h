#pragma once
#include "dxlib.h"
#include"common.h"

struct AttackData {
	float shift_x;			//X���W�ɂ������炷��
	float shift_y;			//Y���W�ɂ������炷��
	float height;			//����
	float width;			//��
	int who_attack;			//�N�̍U����(who�ƍ��킹�Ďg��)
	int attack_time;		//�ǂꂭ�炢���肪���̏�ɋ������邩
	bool direction;			//X���W����ɂ��Ăǂ̕����ɍU���𔭐������邩�̔��f(0=�E 1=��)
	int damage;				//�^����_���[�W��
	int delay;				//���t���[���҂��Ă���U�����邩
	int attack_type;		//�U���̎��(�ߐځA�g��A�e)
	//int effect_type;		//�U���̃A�j���[�V�����̎��
	// 
	//�U���̎�ނ�BULLET�̏ꍇ���̏����������ޕK�v������
	float speed;			//�P�t���[���ɂǂꂾ���O�ɐi�ނ�
	float angle;			//�e�̊p�x(��̌����ɉ����ĕ������ς�邽�߁A0�`0.25�A0.75�`1.0�͈̔͂Ŏw�肷��Ɗ�̑O���֔��)
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
	Location location;			//���S���W
	Location local_location;	//��ʏ�ł̍��W
	Erea erea; //�͈�
	int who;	//�v���C���[���G���A�G�Ȃ�ǂ̎�ނ̉��̖ڂ���ۑ�����
public:

	//�����蔻�� (0,0 = �������Ă��Ȃ� ����ȊO = ����̒��S���W)
	bool HitBox(BoxCollider* bCollider);

	//������W�̎擾
	Location GetLocation()const;

	//���S���W�̎擾
	Location GetCenterLocation()const;

	//���[�J�����W�̎擾
	Location GetLocalLocation()const;

	//���a�̎擾
	Erea GetErea()const;

	//�v���C���[���G���A�G�Ȃ�ǂ̎�ނ̉��̖ڂ����擾����
	int GetWho() { return who; }

	//�I�u�W�F�N�g�̃��[���h���W���X�N���[�����W�ɕϊ�����
	void SetScreenPosition(Location _world_to_screen);
};