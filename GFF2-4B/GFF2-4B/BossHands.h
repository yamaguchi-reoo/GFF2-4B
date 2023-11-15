#pragma once
#include "CharaBase.h"
#include "Rock.h"

class Boss;


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

    /*�U�N����*/
    //�󂯎�����l�ɂ����CMY�̃T�C�Y�ύX�p
    int hands_height[3] = { 190,190,190 };
    int hands_width[3] = { 190,190,190 };

    int Hands_img[IMGMAX];
    int Hands_Img_num;//�摜�؂�ւ��p
    int hi[3];

    //M�̌����~��Ă���X���W
    float Magentax[10] = { 1000,100,500 };

    /*�C���J*/
    int Direction;  //0:������ 1:�E����

    int switching;//���o���ʒu�Z�b�g�p

    bool hitflg=false;
    bool onceflg=true;
    int count;

    bool HitJumpAttack = false;//�W�����v�U�����i�q�b�g�h�~
    bool Death_Flg = false;//HP��0�ɂȂ�����ON
    int Death_Anim;//���S�A�j���[�V�����؂�ւ��p
    
    bool Power_Up;   //������Ԃ��H
    bool Rock_Once; //��o���ʒu��x�����i�[����p
    Location turu_location;  //��`��ʒu
    float turu_angle;        //��p�x
    int turu_img;            //��摜�p

    //�{�X�̏�Ԃ������󂯎��
    int Boss_Form;

    //�ǂ̘r���o�����p 0:�}�[���^ 1:�V�A�� 2:�C�G���[
    int Hands_who;

    int Attack_Num;//�U���̃f�[�^�ǂꑗ�邩���ʗp

    //�Ђ܂��p
    SunFlowerState sf_state;
    bool pos;                //�����̌��ݒn(false = �E�Atrue = ��)
    float sf_speed;          //�ړ����x
    float angle_width;       //�e������������p
    float angle_height;      //�e������������p
    float rad;               //�v�Z�p
    float face_angle;        //��̊p�x
    float move_angle;        //�ړ��̊p�x
    float bullet_angle;      //�e�̊p�x
    float acceleration;      //�ړ��̉����x
    int timer;               //�e���[�V�����̎���
    int attack_cd;           //�e�����p�x
    int attack_combo;        //�e��A���Ō��p
    int attack_num;          //�e��A���Ō��p
    int move_count;          //����ړ��������𑪒肷��     

    BossHands(int _who);
    BossHands(int _who,Boss* boss);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);
    void HandsMagenta(GameMain* main);
    void HandsCyan(GameMain* main);
    void HandsYellow(GameMain* main);

    void ApplyDamage(int num);
    float GetHandsY() { return location.y; };
    float GetHandsX() { return location.x; };

    //���˂����ǂɉ����āA���˂������̊p�x�������_���Ɍ��肷��
    float GetRandAngle(int _wall);
};

