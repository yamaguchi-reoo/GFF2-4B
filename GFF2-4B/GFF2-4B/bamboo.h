#pragma once
#include "BoxCollider.h"
class Bamboo:
    public BoxCollider
{
private:
    bool flg;
public:
    //コンストラクタ
    Bamboo(float pos_y);
    //デストラクタ
    ~Bamboo();

    void Update();
    void Draw()const;

    void ReverseFlg();
};

