#pragma once
#include "CharaBase.h"
#include "Attack.h"

//���z�N���X
class Zakuro :public CharaBase
{
private:
	bool attack_flg;		
	bool direction;					//��̌���(0=�E���� 1=������)
	int stop_count;
public:
	Zakuro();
	~Zakuro();

	void Update(GameMain* main)override;
	void Draw()const override;

	//�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�
	AttackData CreateAttactData();
	void Attack(GameMain*main);
	void Stop_Attack() { attack_flg = false; }


};

