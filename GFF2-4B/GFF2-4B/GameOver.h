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
    int player_lose_image;      //player���s�k�����V�[���ŕ\������摜
    int select_count;           //�Z���N�g�p�̃J�[�\���̓����������J�E���g����ϐ�
    int once_flg;               //�J�[�\�������������ǂ������m�F���邽�߂̃t���O

public:

    //�R���X�g���N�^
    GameOver();
    //�f�X�g���N�^
    ~GameOver();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //�摜�Ǎ���p�֐�
    void ImageLoad(int& _handle, const char* _file_name);
};

