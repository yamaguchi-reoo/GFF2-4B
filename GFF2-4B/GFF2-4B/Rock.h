#pragma once
#include "BoxCollider.h"

class GameMain;

class Rock :
    public BoxCollider
{
private:
    float Rock_x;    //�ₘ
    float Rock_y;    //�ₙ
    float Rock_Movex;    //�ₘ
    float Rock_Movey;    //�ₙ
    float Set_Rock_x;   //X���W�o���ʒu�i�[�p
    float Set_Rock_y;   //Y���W�o���ʒu�i�[�p
    int Rock_img;  //��摜
    float timer;
    float g;//�d�͉����x
    float sita; //�p�x��
    float V_zero; //�����x���O

    int who;

public:
    Rock(int _who,float x,float y);
    ~Rock();

    void Update(GameMain* main);     //�X�V����
    void Draw() const; //�`�揈��
    AttackData RockAttactData();
    void RockAttack(GameMain* main);
    float GetRockx() { return Rock_x; };
    float GetRocky() { return Rock_y; };
};

