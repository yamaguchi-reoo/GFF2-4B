#pragma once
#include "AbstractScene.h"
class GameClear :
    public AbstractScene
{
private:
public:

    GameClear();
    ~GameClear();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

