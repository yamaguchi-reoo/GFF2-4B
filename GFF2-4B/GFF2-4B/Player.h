#pragma once
#include "CharaBase.h"
#include "GameMain.h"
#include "Scroll.h"

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
	JUMPATTACK_RIGHT,
	JUMPATTACK_RIGHT_END,
	JUMPATTACK_LEFT,
	JUMPATTACK_LEFT_END,
	DAMAGE_RIGHT,
	DAMAGE_LEFT,
	DEATH_RIGHT,
	DEATH_LEFT,
};

class Player :
	public CharaBase
{
private:
	Location old_location;			//1�t���[���O�̍��W
	PlayerState player_state;
	float move_speed;				//�ړ����x(���E)
	float jump_power;				//������
	float acs[4];					//�����x 0=������ 1=����� 2=�E���� 3=������
	float acs_max;					//�ő�����x
	int attack_interval_count;		//�U���̊Ԋu����p
	int attack_interval;			//�U���̊Ԋu
	int attack_step;				//�U���̒i�K
	int attack_time;				//�U�����Ă��鎞��
	bool attack_motion_flg;			//�U�����[�V�����������f
	bool direction;					//��̌���(0=�E���� 1=������)
	bool onfloor_flg[FLOOR_NUM];	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
	bool touch_ceil_flg;			//�����ꂩ�̓V��ɐG��Ă��邩�ǂ���
	bool rightwall_flg;				//�����ꂩ�̉E�ǂɐG��Ă��邩�ǂ���
	bool leftwall_flg;				//�����ꂩ�̍��ǂɐG��Ă��邩�ǂ���
	bool apply_gravity;				//�d�͂�K�p���邩�ǂ���
	bool jump_flg;					//�W�����v����
	bool powerup_flg;				//������Ԃ�
	float external_move[4];			//�O����������v���C���[���ړ�������� 0=������ 1=����� 2=�E���� 3=������
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

	//�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�
	AttackData CreateAttactData();

	//������Ԃɓ���
	void SetPowerUp();

	// ������Ԃ���������
	void StopPowerUp();

	//�U���֘A�̏���
	void Attack(GameMain* main);

	//�ړ��֘A�̏���
	void Move();

	//�v���C���[�̏�Ԃ̎擾
	int GetPlayerState() { return (int)player_state; }

	//�v���C���[�̏�Ԃ̍X�V
	void UpdatePlayerState();

	//�v���C���[��HP�̎擾
	int GetPlayerHP() { return hp; }
};

