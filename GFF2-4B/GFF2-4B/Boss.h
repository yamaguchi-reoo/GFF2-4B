#pragma once
#include "CharaBase.h"
class Boss :
    public CharaBase
{
private:
    int bfaceimg;//�{�X�̊�摜

    enum bosshand
    {


    };

public:
    int Count_Death;//�r��������ꂽ���J�E���g�p

    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;

};

