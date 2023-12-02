#pragma once
#include "AbstractScene.h"
#include "common.h"

//�J�b�g�C��01���W
struct CutIn01Pos { float x; float y; };
//�J�b�g�C��02���W
struct CutIn02Pos { float x; float y; };

class GameClear :
    public AbstractScene
{
private:

    //---- �\���̂̕ϐ��� ----//

    CutIn01Pos cut_in01_loc;
    CutIn02Pos cut_in02_loc;

    //--- �J�b�g�C���摜�ۑ��p�ϐ� ---//
    int cut_in01;           //�J�b�g�C���摜1
    int cut_in02;           //�J�b�g�C���摜2

    //�摜����(���B����)�ϐ�
    int stage_goal_image;   //�����摜(���B����)
    int boss_beat_image;    //�����摜(��������)

    //�w�i�摜�p�ϐ�
    int clear_back_image;   //�w�i�摜

    //stage���擾�p�ϐ�
    int stage_num;          //stage���̏����m�ۂ���ϐ�

public:

    //�R���X�g���N�^
    GameClear(int _stage_num);
    //�f�X�g���N�^
    ~GameClear();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //�摜�Ǎ��p�֐�
    void ImageLoad(int& _handle, const char* _file_name);
};

