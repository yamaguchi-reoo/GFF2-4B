#pragma once
#include "AbstractScene.h"
#include "BoxCollider.h"
#include "StageData.h"
#include "Stage.h"
#include "PadInput.h"

#define OBJECT_TYPE_NUM 8   //�z�u�ł���I�u�W�F�N�g�̎�ސ�

 //�G���A�敪
enum SelectErea
{
    STAGE_EDIT=0,
    TOOL_BOX,
};
class EditScene :
    public AbstractScene
{
private:
    int now_select_erea;                                  //���ݑI�𒆂̃G���A(0=�c�[���{�b�N�X 1=�X�e�[�W)
    int now_stage;                                        //���ݕҏW���̃X�e�[�W
    CURSOR cursor;                                        //�}�E�X�J�[�\��
    int stage_data[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];    //�X�e�[�W�̃f�[�^�i�[�p
    int old_stage_data[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];    //�X�e�[�W�̕ύX�O�f�[�^�i�[�p
    Stage* stage[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];      //���̃I�u�W�F�N�g
    int current_type;                                     //���I�΂�Ă���I�u�W�F�N�g�^�C�v
    Location tool_location;                               //�c�[���{�b�N�X�̍�����W
    Erea tool_size;                                       //����̃c�[���{�b�N�X�̕�
    bool select_data[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];  //���̃f�[�^�����ݑI�𒆂��ǂ���

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

    //�ЂƂO�̃f�[�^�̕ێ�
    void SaveOldData();

    //���ǂ̃G���A�ɃJ�[�\�������邩
    int ChechSelectErea(int _i, int _j);

    //�c�[���{�b�N�X����ʊO�ɏo�Ȃ��悤�Ɉړ�����
    void MoveInsideScreen();

    //���ׂẴX�e�[�W�I�u�W�F�N�g���w�肵���l������
    void MoveAllStageObj(int _x, int _y);

    //�ǂ̔����I�𒆂��̏������Z�b�g����
    void ResetSelectData();
};


