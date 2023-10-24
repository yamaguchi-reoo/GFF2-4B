#pragma once
#include "CharaBase.h"
#include "Attack.h"

//���z�N���X
class Zakuro :public CharaBase
{
private:
	Location old_location;	//1�t���[���O�̍��W
	bool zakuro_flg;		//���E�ړ��ifalse = ���@true =�@�E�j
	bool direction;					//��̌���(0=�E���� 1=������)
public:
	Zakuro();
	~Zakuro();

	void Update(GameMain* main)override;
	void Draw()const override;

	//�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�
	AttackData CreateAttactData();
};

