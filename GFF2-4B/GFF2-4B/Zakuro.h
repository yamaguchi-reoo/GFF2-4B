#pragma once
#include "CharaBase.h"
#include "Attack.h"


enum  class ZakuroState {
	IDLE = 0,
	IDLE_RIGHT,
	IDLE_LEFT,
	RIGHT,
	LEFT,
};

//���z�N���X
class Zakuro :public CharaBase
{
private:

	ZakuroState zakuro_state;

	bool attack_flg;	// �U�����Ă��邩	
	int stop_count;		
	bool spawn_flg;		//�X�|�[�����Ă��邩
	bool zakuro_direction;//����(0 = �E 1 = ��)

	//�����蔻��֘A
	bool onfloor_flg;	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
	bool rightwall_flg;				//�����ꂩ�̉E�ǂɐG��Ă��邩�ǂ���
	bool leftwall_flg;				//�����ꂩ�̍��ǂɐG��Ă��邩�ǂ���
	bool apply_gravity;				//�d�͂�K�p���邩�ǂ���

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
	//�����o��(num = �������Ă��鏰 _sub = �������Ă��鏰�̍�����W)
	void ZakuroPush(int num, Location _sub_location, Erea _sub_erea);

	void HitWall();

	//�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�
	AttackData CreateAttactData();
	void Attack(GameMain*main);
	void Stop_Attack() { attack_flg = false; }
	//�_���[�W�󂯂鏈��
	void ApplyDamage(int num);

	void HitZakuro();

	//�X�|�[���t���O�̎擾
	int GetSpwanFlg() { return spawn_flg; }
	ColorDate GetColorDate();
};