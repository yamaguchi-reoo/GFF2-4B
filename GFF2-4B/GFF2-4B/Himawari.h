#pragma once
#include "CharaBase.h"
class Himawari :
    public CharaBase
{
private:
public:
    //�R���X�g���N�^
    Himawari();
    //�f�X�g���N�^
    ~Himawari();

    void Update(GameMain* main)override;
    void Draw()const override;
};

