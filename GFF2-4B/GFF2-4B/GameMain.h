#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Stage.h"
#include "Himawari.h"
#include "Zakuro.h"
#include "Iruka.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;    //�v���C���[�̃I�u�W�F�N�g
    Stage* stage[2];   //���̃I�u�W�F�N�g
    Zakuro* zakuro;    //�U�N��
    Himawari* himawari;//�Ђ܂��
    Iruka* iruka;      //�C���J
    int flg;        //
    int count[2];      //�����p
    bool onfloor_flg;      //�����p
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

