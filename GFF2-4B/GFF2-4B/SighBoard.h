#pragma once
#include "BoxCollider.h"

class SighBoard :
    public BoxCollider

{
private:
    Location disp_location; //�`���[�g���A���\���ʒu
    bool disp_flg;  //�`���[�g���A�����o�������f
    int disp_type;  //�ǂ̊Ŕ��o�������f
    int sb_img[4];     //�Ŕ摜�i�[�p
    int disp_time;  //�\������
public:
    //�R���X�g���N�^
    SighBoard(float pos_x, float pos_y,int type);
    //�f�X�g���N�^
    ~SighBoard();
    void Update(Location _player_location,Location _player_local_location);
    void Draw()const;
};


