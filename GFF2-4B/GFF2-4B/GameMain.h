#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Stage.h"
#include "Himawari.h"
#include "Zakuro.h"

class Himawari;

class GameMain :
    public AbstractScene
{
private:
    Player* player; //�v���C���[�̃I�u�W�F�N�g
    Stage* stage;   //���̃I�u�W�F�N�g
    Zakuro* zakuro;
    Himawari* himawari;
    int flg;        //
    int count;      //�����p

    
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

