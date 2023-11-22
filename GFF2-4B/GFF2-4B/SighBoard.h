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
    bool damage_once;
public:
    //�R���X�g���N�^
    SighBoard(float pos_x, float pos_y,int type);
    //�f�X�g���N�^
    ~SighBoard();
    void Update(Location _player_location,Location _player_local_location);
    void Draw()const;

    //��e(_num = �_���[�W��)
    void ApplyDamage(int _num) { hp -= _num; }
    //��񂾂���e����悤�ɂ���
    bool GetDamageOnce() { return damage_once; }
    void SetDamageOnce(bool _flg) { damage_once = _flg; }
    //hp�擾
    int GetSighBoardHp() { return hp; }
    // 
    bool GetSighFlg() { return tuto_disp_flg; }
    int GetSighTypeFlg() { return disp_type; }
};


