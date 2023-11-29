#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
enum class TITLE_MENU
{
    GAME_START = 0,
    GAME_END
};
class Title :
    public AbstractScene
{
private:

    int title_font;             //�^�C�g�������摜

    int game_start_image;       //�����摜(�J�n:���I�����)
    int game_start_select;      //�����摜(�J�n:�I�����)

    int game_finish_image;      //�����摜(�I��:���I�����)
    int game_finish_select;     //�����摜(�I��:�I�����)

    int Select;                 //�I��
    bool Once;                  //L�X�e�B�b�N�ŃJ�[�\���𓮂����p

    int title_alpha;            //�^�C�g���摜�̓����x
    int font_alpha;             //�t�H���g�摜�̓����x
    int title_x;                //�^�C�g����X���W

public:
    //�R���X�g���N�^
    Title();

    //�f�X�g���N�^
    ~Title();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    void ImageLoad(int& _handle, const char* _file_name);
};


