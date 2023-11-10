#pragma once
#include "CharaBase.h"
class Boss :
    public CharaBase
{
private:
    int bfaceimg;//ボスの顔画像

    enum bosshand
    {


    };

public:
    int Count_Death;//腕が何回やられたかカウント用

    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;

};

