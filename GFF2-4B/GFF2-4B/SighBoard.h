#pragma once
#include "BoxCollider.h"

class SighBoard :
    public BoxCollider

{
private:
    bool disp_flg;  //�`���[�g���A�����o�������f
    int disp_type;  //�ǂ̊Ŕ��o�������f
public:
    //�R���X�g���N�^
    SighBoard(float pos_x, float pos_y,int type);
    //�f�X�g���N�^
    ~SighBoard();
    void Update(Location _player_location);
    void Draw()const;
};


