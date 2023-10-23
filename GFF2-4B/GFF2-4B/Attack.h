#pragma once
#include "BoxCollider.h"

class Attack :
	public BoxCollider
{
private:
	bool attack_flg;	//�U�����������Ă��邩�̃t���O
	bool who_attack;	//�N�̍U�����ifalse = ���� true = �G�j
	int attack_time;	//�ǂꂭ�炢���肪���̏�ɋ������邩
public:
	Attack();
	~Attack();
	void Update(Location _location);
	void Draw()const;
	//�U���𔭐�������(_location = �U�������v���C���[or�G�̒��S���W)
	void SpawnAttack(Location _location);
};
