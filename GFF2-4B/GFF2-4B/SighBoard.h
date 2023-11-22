#pragma once
#include "BoxCollider.h"

class SighBoard :
    public BoxCollider

{
private:
    Location disp_location; //�`���[�g���A���\���ʒu
    int hp;             //���񐔐؂�Ə�����悤��
    bool disp_flg;       //�Ŕ��o�������f
    bool tuto_disp_flg;  //�`���[�g���A�����o�������f
    int disp_type;  //�ǂ̊Ŕ��o�������f
    int sb_img[4];     //�Ŕ摜�i�[�p
    int disp_time;  //�\������
    bool disp_once; //�Ŕt�߂ɂ����Ƃ�����\����������悤��
public:
    //�R���X�g���N�^
    SighBoard(float pos_x, float pos_y,int type);
    //�f�X�g���N�^
    ~SighBoard();
    void Update(Location _player_location,Location _player_local_location);
    void Draw()const;
    void SetDispOnce(bool _flg) { disp_once = _flg; }
    bool GetDispOnce() { return disp_once; }
    // 
    bool GetDispFlg() { return tuto_disp_flg; }
    void SetDispFlg(bool _flg) { tuto_disp_flg = _flg; }
    int GetSighTypeFlg() { return disp_type; }
};


