#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
enum class TITLE_MENU
{
    GAME_START = 0,
    GAME_END
};
class Title :
    public AbstractScene
{
private:
    int Select;     //�I��
    bool Once;      //L�X�e�B�b�N�ŃJ�[�\���𓮂����p

public:
    //�R���X�g���N�^
    Title();

    //�f�X�g���N�^
    ~Title();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};


