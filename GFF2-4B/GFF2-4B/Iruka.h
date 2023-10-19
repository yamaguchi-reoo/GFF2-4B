#pragma once
#include "CharaBase.h"
class Iruka :
    public CharaBase
{
private:
public:
    //コンストラクタ
    Iruka();
    //デストラクタ
    ~Iruka();

    void Update(GameMain* main)override;
    void Draw()const override;
};

