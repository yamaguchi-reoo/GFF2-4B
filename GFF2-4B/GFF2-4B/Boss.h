#pragma once
#include "CharaBase.h"
class Boss :
    public CharaBase
{
private:
    int bfaceimg;//�{�X�̊�摜
    int bhandm;//�{�X��@�}�[���^�̉摜
    int bhandc;//�{�X��@�V�A���̉摜

public:
    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;

};

