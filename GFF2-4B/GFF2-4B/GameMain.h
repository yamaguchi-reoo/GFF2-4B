#pragma once
#include "AbstractScene.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Attack.h"
#include "Stage.h"
#include "Himawari.h"
#include "Zakuro.h"
#include "Iruka.h"
#include "bamboo.h"
#include "Scroll.h"
#include "PowerGauge.h"
#include "PlayerHP.h"
#include "Boss.h"
#include "BossHands.h"

//effect
#include "Effect.h"

#define ATTACK_NUM 100   //��ʂɑ��݂ł���ő�̍U����

class Player;

class GameMain :
    public AbstractScene
{
private:
    Player* player;    //�v���C���[�̃I�u�W�F�N�g
    Stage* stage[FLOOR_NUM];   //���̃I�u�W�F�N�g
    Attack* attack[ATTACK_NUM];     //�U���̃I�u�W�F�N�g

    //�G�l�~�[
    Zakuro* zakuro;    //�U�N��
    Himawari* himawari;//�Ђ܂��
    Iruka* iruka;      //�C���J

    Boss* boss; //�{�X
    BossHands* hands;//�{�X�̘r

    Bamboo* bamboo[BAMBOO_NUM];
    SceneScroll* scene_scroll;  //�X�N���[���N���X�̃I�u�W�F�N�g

    PowerGauge* powergauge;  //�����Q�[�W�̃I�u�W�F�N�g
    PlayerHP* playerhp;  //�v���C���[HPUI�̃I�u�W�F�N�g

    Effect* effect;     //���Ԃ��G�t�F�N�g�̃I�u�W�F�N�g

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

    //�U���𔭐�������(_location = �U�������v���C���[or�G�̒��S���W  _direction = �U���������(0=�E 1=��))
    void SpawnAttack(AttackData _attackdata);

    //�e�����蔻��̏���
    void HitCheck();
};

