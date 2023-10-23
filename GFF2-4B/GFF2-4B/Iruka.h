#pragma once
#include "CharaBase.h"
class Iruka :
    public CharaBase
{
private:
    float fpscount;

    bool iruka_flg;
    bool fall_flg;

public:
    //コンストラクタ
    Iruka();
    //デストラクタ
    ~Iruka();

    void Update(GameMain* main)override;
    void Draw()const override;

    void Get_Fall_Flg() {
        fall_flg = true;
    }

  
};

