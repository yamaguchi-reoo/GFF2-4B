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

    int game_over_image;        //������(�Q�[���I���p)�摜
    int game_continue_image;    //������(�Q�[�����s�p)�摜
    int goal_lose_image;        //player���s�k�����V�[���ŕ\������摜
    int boss_stage_lose_image;  //�{�X�X�e�[�W�ŕ������ꍇ�̕\���摜
    int back_death_image;       //���S�w�i�摜

    int select_count;           //�Z���N�g�p�̃J�[�\���̓����������J�E���g����ϐ�
    int once_flg;               //�J�[�\�������������ǂ������m�F���邽�߂̃t���O
    int stage_num;              //�X�e�[�W���̊m��
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

