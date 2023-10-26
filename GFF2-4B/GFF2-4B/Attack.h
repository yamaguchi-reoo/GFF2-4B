#pragma once
#include "BoxCollider.h"

#define ATTACK_EREA_SHIFT_Y -50	 //�U���͈͂����炷
class Attack :
	public BoxCollider
{
private:
	AttackData attack_data;		//�U���ɕK�v�ȏ��i�[
	bool attack_flg;	//�U�����������Ă��邩�̃t���O
	bool can_apply_damage;		//�_���[�W��^�����邩���f


public:
	Attack();
	~Attack();
	void Update(Location _location, Erea _erea);
	void Draw()const;
	//�U���𔭐�������(_attackdata = �U�������v���C���[�������͓G�̍U���ɕK�v�ȏ��)
	void SpawnAttack(AttackData _attackdata);
	//�U�����������Ă��邩���f
	bool GetAttackFlg() { return attack_flg; }
	//�e�����擾
	AttackData GetAttackData() { return attack_data; }
	//�_���[�W��^�����邩���f
	bool GetCanApplyDamage() { return can_apply_damage; }
	//�U��������
	void DeleteAttack() { attack_flg = false; }
};
