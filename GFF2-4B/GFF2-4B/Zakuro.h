#pragma once
#include "CharaBase.h"
class Zakuro :
    public CharaBase
{
private:
public:
    //�R���X�g���N�^
    Zakuro();
    //�f�X�g���N�^
    ~Zakuro();

    void Update(GameMain* main)override;
    void Draw()const override;
};

