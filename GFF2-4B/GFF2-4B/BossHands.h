#pragma once
#include "CharaBase.h"
class BossHands :
    public CharaBase
{
private:

public:
    int bhandm;//�{�X��@�}�[���^�̉摜
    int bhandc;//�{�X��@�V�A���̉摜
    //�o���[���t�@�C�g�Ɠ����悤�Ȋ����ŉ摜�Ǎ�����

    int handsimg[3];



    int bhandx;
    int bhandy;

    BossHands();
    ~BossHands();

    void Update(GameMain* main)override;
    void Draw()const override;


};

