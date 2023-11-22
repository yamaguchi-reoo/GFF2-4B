#pragma once
#include "CharaBase.h"
#include "Rock.h"

class Boss;

//�Ђ܂��̏��
enum BossHimawariState {
    SF_WAIT = 0,
    SF_MOVE,
    SF_DOWN
};

//���邩�̏��
enum BossIrukaState {
    D_WAIT = 0,
    D_MOVE,
    D_RISE,
    D_DASH,
    D_DOWN
};

//�U�N���̏��
enum BossZakuroState {
    Z_ANIM_UP=0,
    Z_ANIM_FALLING,
    Z_ANIM_DEAD,
    Z_MOVE,
    Z_JUMP_RIGHT,
    Z_JUMP_LEFT,
    Z_FALLING
};

class BossHands :
    public CharaBase
{
private:
#define STOPBOSS (160)  //�{�X�����̍s���ɍs���܂ł̎���
#define IMGMAX (5)      //�{�X�̉摜�ő吔
public:
    //�S�r���ʂŎg��
    int frame;                      //���t���[���o�������ۑ�����p
    int Hands_who;                  //�ǂ̘r���o�����p 0:�}�[���^ 1:�V�A�� 2:�C�G���[
    int Attack_Num;                 //�U���̃f�[�^�ǂꑗ�邩���ʗp
    bool Death_Flg = false;         //HP��0�ɂȂ�����ON
    int Death_Anim;                 //���S�A�j���[�V�����؂�ւ��p
    int Boss_Form;                  //�{�X�̏�Ԃ������󂯎��
    bool HitJumpAttack = false;     //�W�����v�U�����i�q�b�g�h�~
    bool Power_Up;                  //������Ԃ��H
    int Hands_Img_num;              //�摜�؂�ւ��p

    /*�U�N����*/
    //�󂯎�����l�ɂ����CMY�̃T�C�Y�ύX�p
    BossZakuroState zakuro_state;
    int hands_height[3] = { 360,190,190 };
    int hands_width[3] = { 360,190,190 };
    int Hands_img[IMGMAX];
    int Zakuro_img[IMGMAX];

    int Zakuro_Imgnum;//�U�N���̉摜�؂�ւ��p
    int Zakuro_Direction;//�U�N���̌����@�E:0 ��:1
    float Magentax[10] = { 1000,100,500 };    //M�̌����~��Ă���X���W
    int switching;                  //���o���ʒu�Z�b�g�p
    bool hitflg=false;
    bool onceflg=true;
    int count;
    bool Rock_Once;                 //��o���ʒu��x�����i�[����p

    //�U�N���W�����v�p
    float Zakuro_Movex;    //�ړ������U�N����
    float Zakuro_Movey;    //�ړ������U�N����
    float Set_Zakuro_x;   //�U�N���W�����v�J�n�ʒu�i�[�p
    float Set_Zakuro_y;   //�U�N���W�����v�J�n�ʒu�i�[�p
    float time;
    float g;//�d�͉����x
    float sita; //�p�x��
    float V_zero; //�����x���O
    float pi = 3.1415f;
    

    //���邩
    BossIrukaState iruka_state;     //���邩�̏��
    Location turu_location;         //��`��ʒu
    bool rare_flg;                  //�v�������m���ł���
    float iruka_rad;                //���邩�̊p�x�v�Z�p
    float turu_angle;               //��p�x
    float turu_rad;                 //��̕`��p�x�v�Z�p
    int turu_img;                   //��摜�p
    int ref_num;                    //���邩���ǂɒ��˕Ԃ�����
    int tackle_num;                 //���邩���U��������

    //�Ђ܂��
    BossHimawariState hima_state;        //�Ђ܂��̏��
    bool pos;                       //�����̌��ݒn(false = �E�Atrue = ��)
    float sf_speed;                 //�ړ����x
    float angle_width;              //�e������������p
    float angle_height;             //�e������������p
    float rad;                      //�v�Z�p
    float move_angle;               //�ړ��̊p�x
    float bullet_angle;             //�e�̊p�x
    int attack_cd;                  //�e�����p�x
    int attack_combo;               //�e��A���Ō��p
    int attack_num;                 //�e��A���Ō��p
    int move_count;                 //����ړ��������𑪒肷��   

    //���邩�Ђ܂�苤�p
    float acceleration;             //�ړ��̉����x
    float face_angle;               //��̊p�x
    int timer;                      //�e���[�V�����̎���

    BossHands(int _who);
    BossHands(int _who,Boss* boss);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);

    //�}�[���^�i�U�N���j�p�֐�
    void MagentaInit();                     //�}�[���^�i�U�N���j�Ŏg���ϐ�������
    void HandsMagenta(GameMain* main);      //�}�[���^�i�U�N���j�̍X�V

    //�V�A���i�C���J�j�p�֐�
    void CyanInit();                        //�V�A���i�C���J�j�Ŏg���ϐ�������
    void HandsCyan(GameMain* main);         //�V�A���i�C���J�j�̍X�V
    float GetRandAngle(int _wall);          //���˂����ǂɉ����āA���˂������̊p�x�������_���Ɍ��肷��

    //�C�G���[�i�Ђ܂��j�p�֐�
    void YellowInit();                      //�C�G���[�i�Ђ܂��j�Ŏg���ϐ�������
    void HandsYellow(GameMain* main);       //�C�G���[�i�Ђ܂��j�̍X�V


    void ApplyDamage(int num);
    float GetHandsY() { return location.y; };
    float GetHandsX() { return location.x; };
};

