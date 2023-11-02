#pragma once
#include "CharaBase.h"
class BossHands :
    public CharaBase
{
private:

public:
    int bhandm;//ボス手　マゼンタの画像
    int bhandc;//ボス手　シアンの画像
    //バルーンファイトと同じような感じで画像読込する

    int handsimg[3];
    int Magentax[10] = { 1000,100,500 };
    int switching;

    int bhandx;
    int bhandy;
    int down_hand;

    bool hitflg=false;

    BossHands();
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;

    void HandsMagenta();
};

