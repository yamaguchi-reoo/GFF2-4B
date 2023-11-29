#pragma once
#include "BoxCollider.h"

#define ATTACK_EREA_SHIFT_Y -50	 //�U���͈͂����炷
class Attack :
	public BoxCollider
{
private:
	AttackData attack_data;		//�U���ɕK�v�ȏ��i�[
	bool attack_flg;			//�U�����������Ă��邩�̃t���O
	bool can_apply_damage;		//�_���[�W��^�����邩���f
	bool once;					//��񂾂����W�̏���ǂ݂��ށiBullet�p�j
	bool cut_flg;				//�i�Ђ܂��̒e�p�j�U����؂�ꂽ�����f
	int cut_time;				//�؂�ꂽ���o�����鎞��
public:
	Attack();
	~Attack();
	void Update(Location _location, Erea _erea);
	void Draw()const;
	//�U���𔭐�������(_attackdata = �U�������v���C���[�������͓G�̍U���ɕK�v�ȏ�� _location=�����������v���C���[�������͓G�̍��W)
	void SpawnAttack(AttackData _attackdata);
	//�U�����������Ă��邩���f
	bool GetAttackFlg() { return attack_flg; }
	//�e�����擾
	AttackData GetAttackData() { return attack_data; }
	//�_���[�W��^�����邩���f
	bool GetCanApplyDamage() { return can_apply_damage; }
	//�U��������
	void DeleteAttack();
	//�i�Ђ܂��̒e�p�j�U����؂�ꂽ�Ɣ��f����
	void SetCutFlg();
	//�i�Ђ܂��̒e�p�j�U����؂�ꂽ���o�����擾
	bool GetCutFlg() { return cut_flg; }
	//�U�����v���C���[�̊瑤�Ɉړ�������
	void SetDirection(bool _dir) { attack_data.direction = _dir; }
};
