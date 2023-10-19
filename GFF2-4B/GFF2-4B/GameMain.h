#pragma once
#include "AbstractScene.h"
#include "Stage.h"

class GameMain :
    public AbstractScene
{
private:
    Stage* stage;   //���̃I�u�W�F�N�g
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

