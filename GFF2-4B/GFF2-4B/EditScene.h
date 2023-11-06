#pragma once
#include "AbstractScene.h"
#include "BoxCollider.h"
#include "StageData.h"
#include "Stage.h"
#include "PadInput.h"

class EditScene :
    public AbstractScene
{
private:
    int now_stage;          //���ݕҏW���̃X�e�[�W
    CURSOR cursor;      //�}�E�X�J�[�\��
    int STAGE_DATA[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];
    Stage* stage[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];   //���̃I�u�W�F�N�g

    bool select_data[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];
    int flg;               //
    int count[2];          //�����p
    bool onfloor_flg;      //�����p

    int stage_width;        //�X�e�[�W�̃u���b�N�̉��̌� 
    int stage_height;       //�X�e�[�W�̃u���b�N�̏c�̌�
public:
    //�R���X�g���N�^
    EditScene(int _stage);
    //�f�X�g���N�^
    ~EditScene();

    // �`��ȊO�̍X�V������
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //�X�e�[�W�𐶐�����
    void LoadStageData(int _stage);

    //�X�e�[�W�̃t�@�C�����X�V����
    void UpdateStageData(int _stage);

    //�X�e�[�W�̍ēǂݍ���
    void UpdateStage();
};


