#pragma once
#include "BoxCollider.h"

class Player :
	public BoxCollider
{
private:
	float move_speed;		//�ړ����x(���E)
	float jump_power;		//������
	float acs[4]; //�����x 0=������ 1=����� 2=�E���� 3=������

	bool onfloor_flg[FLOOR_NUM];	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
	bool touch_ceil_flg;			//�����ꂩ�̓V��ɐG��Ă��邩�ǂ���
	bool rightwall_flg;			//�����ꂩ�̉E�ǂɐG��Ă��邩�ǂ���
	bool leftwall_flg;			//�����ꂩ�̍��ǂɐG��Ă��邩�ǂ���
	bool apply_gravity;				//�d�͂�K�p���邩�ǂ���
	bool jump_flg;					//�W�����v����
public:
	Player();
	~Player();
	void Update();
	void Draw()const;
	//�d�͂�����
	void GiveGravity();
	//��������(num = ����)
	void DecAcs(int num);
	//���ɐG��Ă��鎞�̏���(num = �������Ă��鏰 _sub = �������Ă��鏰�̒��S���W)
	void OnFloor(int num,Location _sub);
	//�V��ɐG�ꂽ���̏���
	void TouchCeiling();
	//�E�̕ǂɐG�ꂽ���̏���
	void TouchRightWall();	
	//���̕ǂɐG�ꂽ���̏���
	void TouchLeftWall();
	//�����o��(num = �������Ă��鏰 _sub = �������Ă��鏰�̍�����W)
	void Push(int num,Location _sub_location, Erea _sub_erea);
	//�e��������Z�b�g
	void Reset();
	//�v���C���[�̉����ʎ擾 0=������ 1=����� 2=�E���� 3=������
	float GetAcs(int num) { return acs[num]; }
};

