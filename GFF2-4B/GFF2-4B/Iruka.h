#pragma once
#include "CharaBase.h"
class Iruka :
    public CharaBase
{
private:
    float fps_count;//�t���[��

    bool iruka_flg; //���E�ړ��ifalse = ���@true =�@�E�j
    bool fall_flg;  //�����p�t���O
    int direction;	//��̌���(0 = �E���� 1 = ������ 2 = �E�������� 3 = ����������)

public:
    //�R���X�g���N�^
    Iruka();
    //�f�X�g���N�^
    ~Iruka();

    void Update(GameMain* main)override;
    void Draw()const override;

    void Get_Fall_Flg() {
        fall_flg = true;
    }

  
};

