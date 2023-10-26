#pragma once
#include "CharaBase.h"
#include "GameMain.h"
#include "Scroll.h"

#define ATTACK_NUM 5						//�U���̃��p�[�g���[

class GameMain;

enum PlayerState {
	IDOL_RIGHT = 0,
	IDOL_LEFT,
	MOVE_RIGHT,
	MOVE_LEFT,
	JUMP_RIGHT,
	JUMP_LEFT,
	FALL_RIGHT,
	FALL_LEFT,
	ATTACK_RIGHT_ONE,
	ATTACK_RIGHT_TWO,
	ATTACK_RIGHT_THREE,
	ATTACK_RIGHT_FOUR,
	ATTACK_LEFT_ONE,
	ATTACK_LEFT_TWO,
	ATTACK_LEFT_THREE,
	ATTACK_LEFT_FOUR,
	JUMP_ATTACK_RIGHT,
	JUMP_ATTACK_RIGHT_END,
	JUMP_ATTACK_LEFT,
	JUMP_ATTACK_LEFT_END,
	DAMAGE_RIGHT,
	DAMAGE_LEFT,
	DEATH_RIGHT,
	DEATH_LEFT,
};


class Player :
	public CharaBase
{
private:
	int frame;						//�t���[������
	//�ړ��֘A
	Location old_location;			//1�t���[���O�̍��W
	float move_speed;				//�ړ����x(���E)
	float jump_power;				//������
	float acs[4];					//�����x 0=������ 1=����� 2=�E���� 3=������
	float acs_max;					//�ő�����x
	bool direction;					//��̌���(0=�E���� 1=������)
	bool move_flg;					//�������Ԃ�
	float external_move[4];			//�O����������v���C���[���ړ�������� 0=������ 1=����� 2=�E���� 3=������
	bool jump_flg;					//�W�����v����

	//�U���֘A
	AttackData player_attack_data[10];	//�v���C���[�̍U���i�K�Ə�Ԃɉ������f�[�^���܂Ƃ߂Ċi�[���Ă���
	int attack_interval_count;		//�U���̊Ԋu����p
	int attack_interval;			//�U���̊Ԋu
	int ca_interval_count;			//�R���{�U���̊Ԋu����p
	int combo_attack_interval;		//�R���{�U���̊Ԋu
	int attack_step;				//�U���̒i�K
	int attack_time;				//�U�����Ă��鎞��
	bool attack_motion_flg[ATTACK_NUM];		//�U�����[�V�����������f(0����3���ʏ�U���P����S�i�ځ@4=�����U��)
	bool attack_anim_flg;			//�����ꂩ�̍U�����s���Ă���Œ������f
	bool powerup_flg;				//������Ԃ�

	//�����蔻��֘A
	bool onfloor_flg[FLOOR_NUM];	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
	bool touch_ceil_flg;			//�����ꂩ�̓V��ɐG��Ă��邩�ǂ���
	bool rightwall_flg;				//�����ꂩ�̉E�ǂɐG��Ă��邩�ǂ���
	bool leftwall_flg;				//�����ꂩ�̍��ǂɐG��Ă��邩�ǂ���
	bool apply_gravity;				//�d�͂�K�p���邩�ǂ���

	//��e�֘A
	bool inv_flg;					//���G���Ԃ��ǂ���
	bool damage_flg;				//�U������������
	int inv_time;					//���G����
	int damage_time;				//���[�V�����Đ�����

	//�`��֘A
	int player_image[18];					//�v���C���[�摜
	PlayerState player_state;				//�v���C���[�̏�Ԋi�[
	int walk_anim_num[4] = { 0,1,2,1 };		//�����A�j���[�V�����摜�̕`��̏���
	int attack_anim_num[4] = { 0 ,1,2,2 };	//�U���A�j���[�V�����摜�̕`��̏���
	int player_anim;						//�v���C���[�摜�A�j���[�V�����p
	int attack_anim;						//�v���C���[�U���A�j���[�V�����p
	int player_anim_speed;					//�v���C���[�̃A�j���[�V�������x
	bool hidden_flg;						//�摜�_�ŗp

public:
	Player();
	~Player();
	void Update(GameMain* main)override;
	void Draw()const override;

	//�d�͂�����
	void GiveGravity();

	//��������(num = ����)
	void DecAcs(int num);

	//���ɐG��Ă��鎞�̏���(num = �������Ă��鏰 _sub = �������Ă��鏰�̒��S���W)
	void OnFloor(int num,Location _sub);

	//�V��ɐG�ꂽ���̏���
	void TouchCeiling();

	//�E�̕ǂɐG�ꂽ���̏���
	void TouchRightWall();	

	//���̕ǂɐG�ꂽ���̏���
	void TouchLeftWall();

	//�����o��(num = �������Ă��鏰 _sub = �������Ă��鏰�̍�����W)
	void Push(int num,Location _sub_location, Erea _sub_erea);

	//�e��������Z�b�g
	void Reset();

	//�v���C���[�̉����ʎ擾 0=������ 1=����� 2=�E���� 3=������
	float GetAcs(int num) { return acs[num]; }

	//�����I�ȃv���C���[�̈ړ�(_direction = �ړ��������(false=�E���� true=������) _move=�ړ���)
	void ForciblyMovePlayer(ScrollData _scroll);

	//�_���[�W���󂯂����̏���(num = �_���[�W��)
	void ApplyDamage(int num);

	//�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�(i = �ǂ̍U����)
	AttackData CreateAttactData(int i);

	//������Ԃɓ���
	void SetPowerUp();

	// ������Ԃ���������
	void StopPowerUp();

	//�U���֘A�̏���
	void Attack(GameMain* main);

	//�ړ��֘A�̏���
	void Move();

	//�`��֘A�̕ϐ��𓮂�������
	void Anim();

	//�v���C���[�̏�Ԃ̎擾
	int GetPlayerState() { return (int)player_state; }

	//�v���C���[�̏�Ԃ̍X�V
	void UpdatePlayerState();

	//�v���C���[��HP�̎擾
	int GetPlayerHP() { return hp; }

	//�����ꂩ�̏��ɐG��Ă��邩���f����
	bool OnAnyFloorFlg();

	//�����ꂩ�̍U�����s���Ă���Œ������f����
	bool PlayAnyAttack();

	//�v���C���[�̍U���f�[�^���i�[����
	void SetPlayerAttackData();
};

