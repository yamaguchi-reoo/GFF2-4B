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
    CURSOR cursor;      //�}�E�X�J�[�\��
    int STAGE_DATA[STAGE_HEIGHT][STAGE_WIDTH];
    Stage* stage[STAGE_HEIGHT][STAGE_WIDTH];   //���̃I�u�W�F�N�g

    bool select_data[STAGE_HEIGHT][STAGE_WIDTH];
    int flg;               //
    int count[2];          //�����p
    bool onfloor_flg;      //�����p
public:
    //�R���X�g���N�^
    EditScene();
    //�f�X�g���N�^
    ~EditScene();

    // �`��ȊO�̍X�V������
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //�X�e�[�W�𐶐�����
    void CreateStage();

    //�X�e�[�W�̃t�@�C�����X�V����
    void UpdateStageData();
};


