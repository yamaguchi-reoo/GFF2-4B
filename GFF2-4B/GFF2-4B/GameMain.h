#pragma once
#include "AbstractScene.h"
#include "SelectStage.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Attack.h"
#include "StageData.h"
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
#include "Rock.h"
#include "Effect.h"
#include "LoadingScene.h"
#include "Score.h"
#include "SighBoard.h"

class Player;

class GameMain :
    public AbstractScene
{
private:
    int old_stage;//�O�̃X�e�[�W���@�f�o�b�N�p

    int now_stage;      //���݂̃X�e�[�W��
    int STAGE_DATA[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];
    Player* player;                     //�v���C���[�̃I�u�W�F�N�g
    Stage* stage[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];   //���̃I�u�W�F�N�g
    Attack* attack[ATTACK_NUM];     //�U���̃I�u�W�F�N�g

    //�G�l�~�[
    Zakuro* zakuro[ZAKURO_MAX];    //�U�N��
    Himawari* himawari[HIMAWARI_MAX];//�Ђ܂��
    Iruka* iruka[IRUKA_MAX];      //�C���J

    Boss* boss; //�{�X
    BossHands* hands;//�{�X�̘r
    int Check_Num;
    Rock* rock[2];//��

    Bamboo* bamboo[BAMBOO_MAX];
    SceneScroll* scene_scroll;  //�X�N���[���N���X�̃I�u�W�F�N�g

    PowerGauge* powergauge;  //�����Q�[�W�̃I�u�W�F�N�g
    PlayerHP* playerhp;  //�v���C���[HPUI�̃I�u�W�F�N�g
    Score* score; //�X�R�AUI�̃I�u�W�F�N�g

    Effect* effect;     //���Ԃ��G�t�F�N�g�̃I�u�W�F�N�g

    SelectStage* select_stage; //�X�e�[�W�I����ʂ̃I�u�W�F�N�g
    Loading* loading_scene;    //LoadingScene�̃I�u�W�F�N�g

    SighBoard* sighboard[SIGH_BOARD_NUM];      //�Ŕ̃I�u�W�F�N�g

    int flg;               //
    int count[2];          //�����p
    bool onfloor_flg;      //�����p
    int who;                //�N���U�����������f����p

    int stage_width_num;    //�X�e�[�W�u���b�N�̉���
    int stage_height_num;   //�X�e�[�W�u���b�N�̏c��

    int stage_width;        //�X�e�[�W����
public:
    bool Hands_Delete_Flg; //�{�X�̘r�����p

    //�R���X�g���N�^(_stage���ǂݍ��ރX�e�[�W)
    GameMain(int _stage);
    //�f�X�g���N�^
    ~GameMain();

    // �`��ȊO�̍X�V������
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //�U���𔭐�������(_location = �U�������v���C���[or�G�̒��S���W  _direction = �U���������(0=�E 1=��))
    void SpawnAttack(AttackData _attackdata);

    //�e�����蔻��(�v���C���[�Ə��ȊO)�̏���
    void HitCheck();

    //�v���C���[�Ə��̓����蔻�菈��
    void PlayerFloorHitCheck();

    //�X�e�[�W�t�@�C����ǂݍ���
    void LoadStageData(int _stage);

    //���̃X�e�[�W�֑J�ڂ���
    void SetStage(int _stage);

    //�J�������W�̍X�V
    void CameraLocation(Location _location);

    //�J�������W�������n�_�ɖ߂�
    void ResetCamera();

    //�{�X�Ƀv���C���[�̍��W��n���p
    Location GetPlayerLocation();

    //�G�l�~�[��Push���֐���
    template <class T>
    void ProcessCharacterCollision(T* character, Stage* stageObject, int index);
    //�G�l�~�[�̍U�����󂯂鏈��
    template <class T>
    void ProcessAttack(Attack* attack, T* character, Effect* effect);
};

