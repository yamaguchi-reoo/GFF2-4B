#pragma once
#include "CharaBase.h"
enum  class HimawariState {
    IDLE = 0,
    RIGHT,
    LEFT,
    RIGHT_SHOOT,
    LEFT_SHOOT,
    RIGHT_CHARGE,
    LEFT_CHARGE,
    DEATH
};

class Himawari :
    public CharaBase
{
private:
    int anim_frame;     //�A�j���[�V�����t���[������
    int count;			//�J�E���g
    int charge_anim_count; // �`���[�W�A�j���[�V�����̃J�E���^
    HimawariState himawari_state;

    bool attack_flg;    //�U�����Ă��邩
    bool spawn_flg;	    //�X�|�[�����Ă��邩
    bool death_flg;     //����ł��邩
    bool himawari_direction;	//��̌���(0=�E���� 1=������)
    int attack_interval_count;

    //�A�j���[�V����
    int himawari_image[5];			//�U�N���摜
    int himawari_anim;				//�摜�A�j���[�V�����p

    int rapid_fire_interval;
    int bullet_num;
    bool charge_flg;

   int img[10];
   int num;
   int timer;

    //�����蔻��֘A
    bool onfloor_flg;	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
    bool rightwall_flg;				//�����ꂩ�̉E�ǂɐG��Ă��邩�ǂ���
    bool leftwall_flg;				//�����ꂩ�̍��ǂɐG��Ă��邩�ǂ���
    bool apply_gravity;				//�d�͂�K�p���邩�ǂ���
   
public:
    //�R���X�g���N�^
    Himawari(float pos_x, float pos_y, bool direction, int _who);
    //�f�X�g���N�^
    ~Himawari();

    void Update(GameMain* main)override;
    void Draw()const override;

    void HimawariReset();// �����蔻��̃��Z�b�g
    //�d�͂�����
    void HimawariGiveGravity();
    //�����o��(num = �������Ă��鏰 _sub = �������Ă��鏰�̍�����W)
    void Push(int num, Location _sub_location, Erea _sub_erea);
    void Move();
    AttackData CreateAttactData();

    //�U��
    void Attack(GameMain* main);
    //�_���[�W���󂯂鏈��
    void ApplyDamage(int num);
    //�X�|�[���t���O�擾
    int GetSpawnFlg() { return spawn_flg; }
    //hp�擾
    int GetHp() { return hp; }

    void ReverseDirection();
    void ObverseDirection();

    void HimawariAnim();

    ColorDate GetColorDate();
    
};

