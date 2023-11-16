#pragma once
#include "AbstractScene.h"
class GameOver :
    public AbstractScene
{
private:
    int game_over_image;        //������(�Q�[���I���p)�摜
    int game_continue_image;    //������(�Q�[�����s�p)�摜
    int player_lose_image;      //player���s�k�����V�[���ŕ\������摜

public:

    GameOver();
    ~GameOver();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    void ImageLoad(int& _handle, const char* _file_name);
};

