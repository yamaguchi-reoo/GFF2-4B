#pragma once
#include "AbstractScene.h"
class GameMain :
    public AbstractScene
{
private:
    int flg;
public:
    //�R���X�g���N�^
    GameMain();
    //�f�X�g���N�^
    ~GameMain();

    // �`��ȊO�̍X�V������
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

