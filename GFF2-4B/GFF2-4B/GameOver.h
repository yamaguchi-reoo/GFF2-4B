#pragma once
#include "AbstractScene.h"

enum class GAME_OVER_MENU
{
    GAME_MAIN = 0,
    GAME_SELECT
};
class GameOver :
    public AbstractScene
{
private:

    //�����摜�ϐ�
    int game_finish_font;       //�����摜(�I��:���I�����)
    int game_finish_select;     //�����摜(�I��:�I�����)
    int game_continue_font;     //�����摜(���s:���I�����)
    int game_continue_select;   //�����摜(���s:�I�����)
    //�����摜�ϐ�
    int goal_lose_image;        //�����摜(���B���s)
    int boss_stage_lose_image;  //�����摜(�������s)
    //�w�i�摜
    int back_death_image;       //�w�i�摜(Player���|��Ă���摜)
    //�J�[�\���p�ϐ�
    int select_count;           //�Z���N�g�p�̃J�[�\���̓����������J�E���g����ϐ�
    int once_flg;               //�J�[�\�������������ǂ������m�F���邽�߂̃t���O
    //stage�����擾�p�ϐ�
    int stage_num;              //�X�e�[�W���̊m��
    //�����x�p�ϐ�
    float alpha;                //�摜��Y���W

public:

    //�R���X�g���N�^
    GameOver(int _stage_num);
    //�f�X�g���N�^
    ~GameOver();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //�摜�Ǎ���p�֐�
    void ImageLoad(int& _handle, const char* _file_name);
};

