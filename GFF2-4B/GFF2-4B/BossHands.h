#pragma once
#include "CharaBase.h"
class BossHands :
    public CharaBase
{
private:

public:

   // Direction direction;

    int bhandm;//�{�X��@�}�[���^�̉摜
    int bhandc;//�{�X��@�V�A���̉摜
    //�o���[���t�@�C�g�Ɠ����悤�Ȋ����ŉ摜�Ǎ�����

    int hands_height[3] = { 190,190,190 };
    int hands_width[3] = { 190,190,190 };

    int handsimg[3];
    int Magentax[10] = { 1000,100,500 };
    int switching;

    int bhandx;
    int bhandy;
    int down_hand;

    bool hitflg=false;

    BossHands(int _who);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);
    void HandsMagenta();
    void HandResetting();
};

