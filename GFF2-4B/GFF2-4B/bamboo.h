#pragma once
#include "BoxCollider.h"
class Bamboo:
    public BoxCollider
{
private:
    bool flg;
public:
    //�R���X�g���N�^
    Bamboo(float pos_y);
    //�f�X�g���N�^
    ~Bamboo();

    void Update();
    void Draw()const;

    void ReverseFlg();
};

