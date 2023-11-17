#pragma once
#include "CharaBase.h"
class Bamboo:
    public CharaBase
{
private:
    bool spawn_flg;

    bool onfloor_flg;	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
    bool apply_gravity;		//�d�͂�K�p���邩�ǂ���
public:
    //�R���X�g���N�^
    Bamboo(float pos_x, float pos_y);
    //�f�X�g���N�^
    ~Bamboo();


    void BambooReset();// �����蔻��̃��Z�b�g
    //�d�͂�����
    void BambooGiveGravity();
    //�����o��(num = �������Ă��鏰 _sub = �������Ă��鏰�̍�����W)
    void Push(int num, Location _sub_location, Erea _sub_erea);

    void Update(GameMain* main)override;
    void Draw()const override;

    //�_���[�W���󂯂鏈��
    void ApplyDamage(int num);
    //�X�|�[���t���O�擾
    int GetSpwanFlg() { return spawn_flg; }

    void FalseGravity();

};

