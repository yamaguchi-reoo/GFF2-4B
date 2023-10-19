#pragma once
#include "BoxCollider.h"

class Player :
	public BoxCollider
{
private:
	float acs[4]; //�����x 0=������ 1=����� 2=�E���� 3=������

	bool onfloor_flg;	//�n�ʂɐG��Ă��邩�ǂ���
public:
	Player();
	~Player();
	void Update();
	void Draw()const;
	//�d�͂�����
	void GiveGravity();
	//��������
	void DecAcs(int num);
	//���ɐG��Ă��鎞�̏���
	void OnFloor();
	//���ɐG��Ă��Ȃ����̏���
	void NotOnFloor();
	//�����o��
	void Push(int num);
};
