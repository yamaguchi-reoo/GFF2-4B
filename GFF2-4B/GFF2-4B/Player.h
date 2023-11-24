#pragma once
#include "CharaBase.h"
#include "GameMain.h"
#include "Scroll.h"

#define ATTACK_PATTERN 6  //�v���C���[�̍U���̃��p�[�g���[

//�z�Q�Ɩh�~
class GameMain;

//�v���C���[�̏��
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

//�v���C���[�̏��(������) �f�o�b�O�\���p
#ifdef _DEBUG
static char player_state_char[24][256]{
	"IDOL_RIGHT",
	"IDOL_LEFT",
	"MOVE_RIGHT",
	"MOVE_LEFT",
	"JUMP_RIGHT",
	"JUMP_LEFT",
	"FALL_RIGHT",
	"FALL_LEFT",
	"ATTACK_RIGHT_ONE",
	"ATTACK_RIGHT_TWO",
	"ATTACK_RIGHT_THREE",
	"ATTACK_RIGHT_FOUR",
	"ATTACK_LEFT_ONE",
	"ATTACK_LEFT_TWO",
	"ATTACK_LEFT_THREE",
	"ATTACK_LEFT_FOUR",
	"JUMP_ATTACK_RIGHT",
	"JUMP_ATTACK_RIGHT_END",
	"JUMP_ATTACK_LEFT",
	"JUMP_ATTACK_LEFT_END",
	"DAMAGE_RIGHT",
	"DAMAGE_LEFT",
	"DEATH_RIGHT",
	"DEATH_LEFT",
};
#endif

class Player :
	public CharaBase
{
private:

#ifdef _DEBUG
	bool d_inv_flg;					//���G���ǂ����i�f�o�b�O�p�j
#endif
	int frame;						//�t���[������

	//�ړ��֘A
	Location old_location;			//1�t���[���O�̍��W
	Location next_location;			//1�t���[����̍��W
	float move_speed;				//�ړ����x(���E)
	float jump_power;				//������
	float acs[4];					//�����x 0=������ 1=����� 2=�E���� 3=������
	float acs_max;					//�ő�����x
	bool direction;					//��̌���(0=�E���� 1=������)
	bool move_flg;					//�������Ԃ�
	float external_move[4];			//�O����������v���C���[���ړ�������� 0=������ 1=����� 2=�E���� 3=������
	bool jump_flg;					//�W�����v����
	int player_now_erea;			//�����̍��W�̎��͂ɂ���X�e�[�W�u���b�N���炵�������蔻������Ȃ��悤�ɂ���

	//�U���֘A
	AttackData player_attack_data[ATTACK_NUM * 2];	//�v���C���[�̍U���i�K�Ə�Ԃɉ������f�[�^���܂Ƃ߂Ċi�[���Ă���
	int attack_interval_count;						//�U���̊Ԋu����p
	int attack_interval;							//�U���̊Ԋu
	int ca_interval_count;							//�R���{�U���̊Ԋu����p
	int combo_attack_interval;						//�R���{�U���̊Ԋu
	int attack_step;								//�U���̒i�K
	int attack_time;								//�U�����Ă��鎞��
	int attack_time_count;							//�U�����Ă��鎞�ԑ���p
	bool attack_motion_flg[ATTACK_NUM];				//�U�����[�V�����������f(0����3���ʏ�U���P����S�i�ځ@4=�����U��)
	bool attack_anim_flg;							//�����ꂩ�̍U�����s���Ă���Œ������f
	bool powerup_flg;								//������Ԃ�

	//�����蔻��֘A
	bool onfloor_flg;				//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
	bool touch_ceil_flg;			//�����ꂩ�̓V��ɐG��Ă��邩�ǂ���
	bool rightwall_flg;				//�����ꂩ�̉E�ǂɐG��Ă��邩�ǂ���
	bool leftwall_flg;				//�����ꂩ�̍��ǂɐG��Ă��邩�ǂ���
	bool apply_gravity;				//�d�͂�K�p���邩�ǂ���

	//��e�֘A
	bool inv_flg;					//���G���Ԃ��ǂ���
	bool damage_flg;				//�U������������
	int inv_time;					//���G����
	int damage_time;				//���[�V�����Đ�����
	bool death_flg;					//���S�������ǂ���
	int death_time;					//���S���o������

	//�`��֘A
	int player_image[35];					//�v���C���[�摜
	PlayerState player_state;				//�v���C���[�̏�Ԋi�[
	//�U���A�j���[�V�����摜�̕`��̏���
	int attack_anim_num[5][12] = { 
		{ 0,0,1,1,2,2,3,4,4,5,5,5} ,
		{ 0,0,1,1,2,2,3,3,4,4,5,5} ,
		{ 0,0,1,1,2,3,4,4,5,5,6,6} ,
		{ 0,0,0,1,1,2,3,4,5,5,5,5} ,
		{ 0,0,0,0,1,-6,-6,-6,-6,-6,-6,-6} ,
		};	
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
	void OnFloor();

	//�����o��( _sub = �������Ă��鏰�̍�����W _type = �����������̎��)
	void Push(Location _sub_location, Erea _sub_erea, int _type);

	//�e��������Z�b�g
	void Reset();

	//�v���C���[�̉����ʎ擾 0=������ 1=����� 2=�E���� 3=������
	float GetAcs(int num) { return acs[num]; }

	//�����I�ȃv���C���[�̈ړ�(_direction = �ړ��������(false=�E���� true=������) _move=�ړ���)
	void ForciblyMovePlayer(ScrollData _scroll);

	//�_���[�W���󂯂����̏���(num = �_���[�W��)
	void ApplyDamage(GameMain* main,int num);

	//�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�(i = �ǂ̍U����)
	AttackData CreateAttactData(int i);

	//������Ԃɓ���
	void SetPowerUp();

	//������Ԃ���������
	void StopPowerUp();

	//�U���֘A�̏���
	void Attack(GameMain* main);

	//�ړ��֘A�̏���
	void Move(GameMain* main);

	//�`��֘A�̕ϐ��𓮂�������
	void Anim();

	//�v���C���[�̏�Ԃ̎擾
	//int GetPlayerState() { return (int)player_state; }

	//�v���C���[�̏�Ԃ̍X�V
	void UpdatePlayerState();

	//�v���C���[��HP�̎擾
	int GetPlayerHP() { return hp; }

	//�����ꂩ�̍U�����s���Ă���Œ������f����
	bool PlayAnyAttack();

	//�w�肵���U���̃t���O��true�ɂ��A����ȊO�̃t���O��false�ɂ���
	void SetAttackFlg(int num);

	//�v���C���[�̍U���f�[�^���i�[����
	void SetPlayerAttackData();

	//�v���C���[�����X�|�[��������(_location=�X�|�[��������ꏊ)
	void Respawn(Location _location);

	//�v���C���[�����ݍs���Ă���U�����擾
	int GetAttackStep() { return attack_step; }

	//�v���C���[�����ɐG��Ă��邩�擾
	bool GetOnFloorFlg() { return onfloor_flg; }

	//�v���C���[�̊�̌���
	bool GetPlayerDirection() { return direction; }

	//�v���C���[��������G���A���擾
	int GetPlayerNowErea() { return player_now_erea; }

	//�P�}�X�ړ����ɏ��Ƃ̓����蔻����`�F�b�N����
	void MoveLocation(GameMain* main,float _x, float _y);

	void AddPlayerHp() { hp += 1; }
};

