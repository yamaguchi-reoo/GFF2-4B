#pragma once
#include "CharaBase.h"
#include "Attack.h"

//���z�N���X
class Zakuro :public CharaBase
{
private:

	Direction direction;

	bool attack_flg;		
	//bool direction;		//��̌���(0=�E���� 1=������)
	int stop_count;		
	bool spawn_flg;		//�X�|�[�����Ă��邩

public:
	Zakuro();
	~Zakuro();

	void Update(GameMain* main)override;
	void Draw()const override;
	void Move(); //���E�ړ�
	void MoveNockBack();//�m�b�N�o�b�N

	//�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�
	AttackData CreateAttactData();
	void Attack(GameMain*main);
	void Stop_Attack() { attack_flg = false; }
	//�_���[�W�󂯂鏈��
	void ApplyDamage(int num);

	int GetSpwanFlg() { return spawn_flg; }
	ColorDate GetColorDate();
};

