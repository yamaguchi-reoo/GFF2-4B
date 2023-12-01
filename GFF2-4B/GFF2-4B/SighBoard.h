#pragma once
#include "CharaBase.h"

class SighBoard :
    public BoxCollider

{
private:
    ColorDate Date{ 0 };
    int frame;                  //�t���[������
    Location disp_location;     //�`���[�g���A���\���ʒu
    bool disp_flg;              //�Ŕ��o�������f
    bool tuto_disp_flg;         //�`���[�g���A�����o�������f
    int disp_type;              //�ǂ̊Ŕ��o�������f
    int sb_img[4];              //�Ŕ摜�i�[�p
    bool disp_once;             //��x�\�����ꂽ�Ŕ͓�x�ƕ\�����Ȃ��悤��
    int hp;                     //���񐔐؂�Ə�����悤��
    bool break_flg;             //�Ŕ�j�󂷂�
    bool direction;             //������ԕ���
    float acs[4];               //�����x 0=������ 1=����� 2=�E���� 3=������

public:
    //�R���X�g���N�^
    SighBoard(float pos_x, float pos_y,int type);
    //�f�X�g���N�^
    ~SighBoard();

    void Update(int _stage_height ,Location _player_location,Location _player_local_location);
    void Draw()const;

    //��������(num = ����)
    void DecAcs(int num);

    //�\���o���邩�擾����
    bool GetDispOnce() { return disp_once; }

    //�\�����邩�̃t���O���Z�b�g����
    void SetDispOnce(bool _flg) { disp_once = _flg; }

    //�`���[�g���A���\���������擾����
    bool GetDispFlg() { return tuto_disp_flg; }

    //�`���[�g���A���\��������ݒ肷��
    void SetDispFlg(bool _flg) { tuto_disp_flg = _flg; }

    //�ǂ̎�ނ̊Ŕ����擾����
    int GetSighTypeFlg() { return disp_type; }

    //�Ŕ�HP�����炵�āA���炵�����HP���擾����
    int ApplyDamage(int _num) {
        hp -= _num;
        return hp;
    }

    //�j��\�ɂ���
    void SetBreak(bool _player_direction);   

    //�j��\�t���O�������Ă��邩���f
    bool GetBreakFlg() { return break_flg; }

    //�F�̎擾
    ColorDate GetColorDate(){ return Date; }
};


