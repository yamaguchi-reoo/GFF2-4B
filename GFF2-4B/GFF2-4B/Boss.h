#pragma once
#include "CharaBase.h"
class Boss :
    public CharaBase
{
private:
    int bfaceimg;//ƒ{ƒX‚ÌŠç‰æ‘œ


    enum bosshand
    {


    };

public:
    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;

};

