#pragma once
#include "CharaBase.h"
#include "Attack.h"

enum  class ZakuroState {
	IDLE = 0,
	RIGHT,
	LEFT,
};

//���z�N���X
class Zakuro :public CharaBase
{
private:

	ZakuroState zakuro_state;

	bool attack_flg;		
	int stop_count;		
	bool spawn_flg;		//�X�|�[�����Ă��邩
	bool zakuro_direction;

	//�����蔻��֘A
	bool onfloor_flg[FLOOR_NUM];	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
	bool touch_ceil_flg;			//�����ꂩ�̓V��ɐG��Ă��邩�ǂ���
	bool rightwall_flg;				//�����ꂩ�̉E�ǂɐG��Ă��邩�ǂ���
	bool leftwall_flg;				//�����ꂩ�̍��ǂɐG��Ă��邩�ǂ���
	bool apply_gravity;				//�d�͂�K�p���邩�ǂ���

public:
	Zakuro();
	~Zakuro();

	void Update(GameMain* main)override;
	void Draw()const override;
	void Move(); //���E�ړ�
	void MoveNockBack();//�m�b�N�o�b�N
	void ZakuroReset();
	//�d�͂�����
	void ZakuroGiveGravity();
	//�����o��(num = �������Ă��鏰 _sub = �������Ă��鏰�̍�����W)
	void ZakuroPush(int num, Location _sub_location, Erea _sub_erea);
	//���ɐG��Ă��鎞�̏���(num = �������Ă��鏰 _sub = �������Ă��鏰�̒��S���W)
	void ZakuroOnFloor(int num, Location _sub);

	//�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�
	AttackData CreateAttactData();
	void Attack(GameMain*main);
	void Stop_Attack() { attack_flg = false; }
	//�_���[�W�󂯂鏈��
	void ApplyDamage(int num);

	int GetSpwanFlg() { return spawn_flg; }
	ColorDate GetColorDate();
};

