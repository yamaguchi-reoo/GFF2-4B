#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Stage.h"
#include "Himawari.h"
#include "Zakuro.h"
#include "Iruka.h"
#include "bamboo.h"
#include "Scroll.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;    //�v���C���[�̃I�u�W�F�N�g
    Stage* stage[2];   //���̃I�u�W�F�N�g

    //�G�l�~�[
    Zakuro* zakuro;    //�U�N��
    Himawari* himawari;//�Ђ܂��
    Iruka* iruka;      //�C���J

    Bamboo* bamboo[BAMBOO_NUM];
    //SceneScroll* scene_scroll;  //�X�N���[���N���X�̃I�u�W�F�N�g

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

