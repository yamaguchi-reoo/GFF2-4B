#pragma once
#include "AbstractScene.h"
class GameOver :
    public AbstractScene
{
private:
public:

    GameOver();
    ~GameOver();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

