#pragma once
#include "BoxCollider.h"

class GameMain;
class BossHands;

class Rock :
    public BoxCollider
{
private:
    //M�̌����~��Ă���X���W
    float Rock_X[10] = { 1000,100,500,600 };


    float Rock_Movex;    //�ړ������ₘ
    float Rock_Movey;    //�ړ������ₙ
    float Set_Rock_x;   //X���W�o���ʒu�i�[�p
    float Set_Rock_y;   //Y���W�o���ʒu�i�[�p
    int Rock_img;  //��摜
    float timer;
    float g;//�d�͉����x
    float sita; //�p�x��
    float V_zero; //�����x���O

    int Set_xnum;//��o�����W�󂯎��
    
    BossHands* hands;

public:
    bool Rock_Delete;//��������p

    Rock(int _who,int Set_Xnum);
    ~Rock();

    void Update(GameMain* main);     //�X�V����
    void Draw() const; //�`�揈��
    AttackData RockAttactData();
    void RockAttack(GameMain* main);
};

