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
    int Boss_Form;//���ǂ̌`�Ԃ� 0:���`�� 1:���`�� 3:�ŏI�`��

    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;
    int GetBossForm() { return Boss_Form; };
};

