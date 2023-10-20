#pragma once
#include "BoxCollider.h"

class Player :
	public BoxCollider
{
private:
	float acs[4]; //�����x 0=������ 1=����� 2=�E���� 3=������

	bool onfloor_flg[FLOOR_NUM];	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
	bool apply_gravity;				//�d�͂�K�p���邩�ǂ���
public:
	Player();
	~Player();
	void Update();
	void Draw()const;
	//�d�͂�����
	void GiveGravity();
	//��������(num = ����)
	void DecAcs(int num);
	//���ɐG��Ă��鎞�̏���(num = �������Ă��鏰)
	void OnFloor(int num);
	//���ɐG��Ă��Ȃ����̏���(num = �������Ă��鏰)
	void NotOnFloor(int num);
	//�V��ɐG�ꂽ���̏���
	void TouchCeiling(int num);
	//�����o��(num = �������Ă��鏰 _sub = �������Ă��鏰�̒��S���W)
	void Push(int num,Location _sub);
};
