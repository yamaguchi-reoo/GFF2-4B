#pragma once
#include "CharaBase.h"
class Himawari :
    public CharaBase
{
private:
public:
    //コンストラクタ
    Himawari();
    //デストラクタ
    ~Himawari();

    void Update(GameMain* main)override;
    void Draw()const override;
};

