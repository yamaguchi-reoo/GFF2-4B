#pragma once
#include "CharaBase.h"

enum  class ZakuroState {
	IDLE = 0,
	IDLE_RIGHT,
	IDLE_LEFT,
	RIGHT,
	LEFT,
	DEATH
};

//���z�N���X
class Zakuro :public CharaBase
{
private:

	ZakuroState zakuro_state;

	int anim_frame;     //�A�j���[�V�����t���[������
	int count;			//�J�E���g

	bool attack_flg;	// �U�����Ă��邩	
	int stop_count;		
	bool spawn_flg;		//�X�|�[�����Ă��邩
	bool zakuro_direction;//����(0 = �E 1 = ��)
	bool knockback_flg;

	//�����蔻��֘A
	bool onfloor_flg;	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
	bool rightwall_flg;				//�����ꂩ�̉E�ǂɐG��Ă��邩�ǂ���
	bool leftwall_flg;				//�����ꂩ�̍��ǂɐG��Ă��邩�ǂ���
	bool apply_gravity;				//�d�͂�K�p���邩�ǂ���
	bool hit_flg; 

public:
	Zakuro(float pos_x, float pos_y, bool direction, int _who);
	~Zakuro();

	void Update(GameMain* main)override;
	void Draw()const override;
	void Move(); //���E�ړ�
	void MoveNockBack();//�m�b�N�o�b�N
	void ZakuroReset();// �����蔻��̃��Z�b�g
	//�d�͂�����
	void ZakuroGiveGravity();
	//�����o��( _sub = �������Ă��鏰�̍�����W _type = �����������̎��)
	void Push(int num, Location _sub_location, Erea _sub_erea);

	//void Push(Location _sub_location, Erea _sub_erea, int _type);
	void HitWall();

	//�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�
	AttackData CreateAttactData();
	void Attack(GameMain*main);
	//�U����~
	void Stop_Attack() { attack_flg = false; }
	//�_���[�W�󂯂鏈��
	void ApplyDamage(int num);
	//�U�N�����m�������������̏���
	void HitZakuro();
	//HP�̎擾
	int GetHp() { return hp; }
	//�X�|�[���t���O�̎擾
	int GetSpwnFlg() { return spawn_flg; }

	int GetAttackFlg() { return attack_flg; }
	//�A�j���[�V����
	//void ZakuroAnim();
	//�����̔��]
	//void ReverseDirection();

	ZakuroState GetZakuroState(){return zakuro_state;}
	ColorDate GetColorDate();

};
