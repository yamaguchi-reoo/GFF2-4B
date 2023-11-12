#pragma once
#include "CharaBase.h"
#include "Rock.h"

class Boss;

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
    int hi[3];
    int bosf[3];

    //M�̌����~��Ă���X���W
    float Magentax[10] = { 1000,100,500 };

    /*�C���J*/

    int switching;

    int bhandx;
    int bhandy;
    int down_hand;

    bool hitflg=false;
    bool onceflg=true;
    int count;
    bool Hit_Once;

    bool HitJumpAttack = false;
    bool Death_Flg = false;
    
    bool Power_Up;   //������Ԃ��H
    bool Rock_Once; //�o���ʒu��x�����i�[����p

    //�{�X�̏�Ԃ������󂯎��
    int Boss_Form;

    int Attack_Num;//�{�X�̎肪�����̍U�����Ă��邩

    BossHands(int _who,Boss* boss);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);
    void HandsMagenta(GameMain* main);
    void ApplyDamage(int num);
    float GetHandsY() { return location.y; };
    float GetHandsX() { return location.x; };
};

