#pragma once
#include "CharaBase.h"
class Iruka :
    public CharaBase
{
private:
public:
    //�R���X�g���N�^
    Iruka();
    //�f�X�g���N�^
    ~Iruka();

    void Update(GameMain* main)override;
    void Draw()const override;
};

