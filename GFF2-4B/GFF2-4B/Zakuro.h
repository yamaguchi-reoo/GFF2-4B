#pragma once
#include "CharaBase.h"
class Zakuro :
    public CharaBase
{
private:
public:
    //コンストラクタ
    Zakuro();
    //デストラクタ
    ~Zakuro();

    void Update(GameMain* main)override;
    void Draw()const override;
};

