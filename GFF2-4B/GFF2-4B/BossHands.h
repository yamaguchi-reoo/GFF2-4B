#pragma once
#include "CharaBase.h"

//�Ђ܂��̏��
enum SunFlowerState {
    WAIT = 0,
    MOVE,
    DOWN
};

class BossHands :
    public CharaBase
{
private:
#define STOPBOSS (160)  //�{�X�����̍s���ɍs���܂ł̎���
#define IMGMAX (5)      //�{�X�̉摜�ő吔
public:

    //�󂯎�����l�ɂ����CMY�̃T�C�Y�ύX�p
    int hands_height[3] = { 190,190,190 };
    int hands_width[3] = { 190,190,190 };

    int Hands_img[IMGMAX];

    //M�̌����~��Ă���X���W
    int Magentax[10] = { 1000,100,500 };

    int switching;

    int bhandx;
    int bhandy;
    int down_hand;

    bool hitflg=false;
    bool onceflg=true;
    int count;
    bool Hit_Once;

    int Attack_Num;//�{�X�̎肪�����̍U�����Ă��邩

    //�Ђ܂��p
    SunFlowerState sf_state;
    bool pos;                //�����̌��ݒn(false = �E�Atrue = ��)
    float sf_speed;          //�ړ����x
    float angle_width;       //�e������������p
    float angle_height;      //�e������������p
    float move_angle;        //�ړ��̊p�x
    float bullet_angle;      //�e�̊p�x
    float acceleration;      //�ړ��̉����x
    int timer;               //�e���[�V�����̎���
    int attack_cd;           //�e�����p�x

    BossHands(int _who);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);
    void HandsMagenta(GameMain* main);
    void HandsYellow(GameMain* main);

    void ApplyDamage(int num);
};

