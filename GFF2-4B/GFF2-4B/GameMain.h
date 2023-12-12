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
#include "HealItem.h"
#include "Koban.h"
#include "Jar.h"

class Player;

class GameMain :
    public AbstractScene
{
private:
    bool pause_flg;     //�|�[�Y��ʗp
    bool tuto_flg; //�`���[�g���A���\������
    int old_stage;//�O�̃X�e�[�W���@�f�o�b�N�p
    int now_tuto;   //���ݕ\������Ă���`���[�g���A��
    int now_stage;      //���݂̃X�e�[�W��
    bool game_over_flg;     //�Q�[���I�[�o�[�̏����𖞂�������t���O�𗧂Ă�
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
    HealItem* heal[ITEM_MAX];     //�񕜃A�C�e��
    Koban* koban[KOBAN_NUM]; //����
    Score* score; //�X�R�AUI�̃I�u�W�F�N�g

    Jar* jar[JAR_MAX]; //��

    Effect* effect[SPLASH_MAX];     //���Ԃ��G�t�F�N�g�̃I�u�W�F�N�g

    SelectStage* select_stage; //�X�e�[�W�I����ʂ̃I�u�W�F�N�g
    Loading* loading_scene;    //LoadingScene�̃I�u�W�F�N�g

    SighBoard* sighboard[SIGH_BOARD_NUM];      //�Ŕ̃I�u�W�F�N�g

    int torii_image[2];
    Location goal_location;
    int flg;               //
    int count[2];          //�����p
    int who;                //�N���U�����������f����p
    
    int stage_width_num;    //�X�e�[�W�u���b�N�̉���
    int stage_height_num;   //�X�e�[�W�u���b�N�̏c��
    int stage_width;        //�X�e�[�W����
    int stage_height;        //�X�e�[�W�c��
    bool camera_x_lock_flg;   //�J�����������邩���f(�����퓬���ȊO)
    bool camera_y_lock_flg;   //�J�����������邩���f(�����퓬���ȊO)
    bool x_pos_set_once; //�J�����̃��b�N�ʒu�ݒ�p
    bool y_pos_set_once; //�J�����̃��b�N�ʒu�ݒ�p
    Location lock_pos;      //�J�����������Ȃ����ɉ�ʗh�ꂪ�����������A�J�����̈ʒu���߂�ꏊ

    int Back_Img;//�X�e�[�W�w�i
    int Pause_Img;      //�ꎞ��~
    int impact_timer;               //��ʗh�ꉉ�o

    int distinguish;        // �|�ƚ����������
    int item_rand;

    int lock_flg; //�����퓬���̃t���O
    bool battle_once_flg[BATTLE_ZONE_NUM];      //�e�����퓬�]�[������񂾂���������p
    Location battle_start_pos[BATTLE_ZONE_NUM] = { {-100,-100} ,{-100,-100} ,{-100,-100} ,{-100,-100} ,{-100,-100} };   //�퓬���n�܂���W
    int now_battle;                  //���݂ǂ��̃G���A�ŋ����퓬���N���Ă��邩���f (-1=�ǂ��ł�����Ă��Ȃ�)
    Location vine1;                 //���[�̖��̍��W�i���E�̖��̊Ԃ̍��W�������Ă���j
    Location vine2;                 //�E��̖��̍��W
    Location vine3;                 //����̖��̍��W
    int vine_img[2]; //���A���̉摜
    int venemy_cnt;  //�G�̐������ԃJ�E���g
    int venemy_num1; //�����퓬���ɐ��������G�̐�
    int venemy_num2; //�����퓬���Ɏa�����G�̐�

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
    void HitCheck(GameMain* main);

    //�v���C���[�Ə��̓����蔻�菈��
    void PlayerFloorHitCheck();

    //�X�e�[�W�t�@�C����ǂݍ���
    void LoadStageData(int _stage);

    //���̃X�e�[�W�֑J�ڂ���
    void SetStage(int _stage);

    //�J�������W�̍X�V
    void CameraLocation(float _x, float _y);

    //�J�������W�������n�_�ɖ߂�
    void ResetCamera();

    //�v���C���[�ɃX�e�[�W�̍�����n���p
    int GetStageHeight() { return stage_height; }

    //�X�e�[�W�ɑ��̃X�e�[�W��type����n���p
    int GetStageType(int _i, int _j);

    //�{�X�Ƀv���C���[�̍��W��n���p
    Location GetPlayerLocation();

    //�J������h�炷�p�̕ϐ���ݒ肷��(_power = �h��Ă��鎞�ԂƋ��x)
    void ImpactCamera(int _power);

    //�J�����̍X�V���J������h�炷
    void UpdateCamera();

    //�J�����ʒu�̎擾
    Location GetCameraLocation();

    //�Q�[���I�[�o�[�̃t���O�𗧂Ă�
    void SetGameOver() { game_over_flg = true; }
    //�G�l�~�[��Push���֐���
    template <class T>
    void ProcessCharacterCollision(T* character, Stage* stageObject);
    //�|�ƃG�l�~�[�̓����蔻��
    template <class T>
    void HitBamboo(T* character);
    //�G�l�~�[�̍U�����󂯂鏈��
    template <class T>
    void ProcessAttack(Attack* attack, T* character /*,Effect* effect/*,HealItem* heal, Koban* koban*/);
    //�A�C�e���̃����_���o��
    template<class T>
    void ItemSpwanRand(T* character);

    //�G�t�F�N�g�̏o��
    template<class T>
    void SpawnEffect(T* character);
    //�v���C���[�ƒ|����̓����蔻��
    template<class T>
    void HitPlayer(Attack* attack, T* object);

    //�����ł̓G��������
    void VineEnemy(void);

    //�����퓬�]�[���֘A����
    void BattleZone();
};

