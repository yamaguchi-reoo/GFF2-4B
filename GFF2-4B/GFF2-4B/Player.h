#pragma once
#include "BoxCollider.h"

class Player :
	public BoxCollider
{
private:
	float acs[4]; //�����x 0=������ 1=����� 2=�E���� 3=������
public:
	Player();
	~Player();
	void Update();
	void Draw()const;
	//�d�͂�����
	void GiveGravity();
	//��������
	void DecAcs(int num);
};
