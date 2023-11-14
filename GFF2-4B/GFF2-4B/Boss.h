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
    int Boss_Form;//今どの形態か 0:第一形態 1:第二形態 3:最終形態

    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;
    int GetBossForm() { return Boss_Form; };
};

