#pragma once
#include "CharaBase.h"
class Boss :
    public CharaBase
{
private:
    int bfaceimg;//ボスの顔画像
    int bhandm;//ボス手　マゼンタの画像
    int bhandc;//ボス手　シアンの画像

public:
    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;

};

