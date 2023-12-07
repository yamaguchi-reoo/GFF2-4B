#pragma once
#include "CharaBase.h"
enum  class BambooState {
    IDLE = 0,
    DEATH
};
class Bamboo:
    public CharaBase
{
private:
    ColorDate Date{ 0 };
    int anim_frame;     //�A�j���[�V�����t���[������
    int count;			//�J�E���g
    BambooState bamboo_state;

    bool spawn_flg;
    bool death_flg;
    int bamboo_image[4];
    int bamboo_anim;

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
    bool ApplyDamage(int num);
    //�X�|�[���t���O�擾
    int GetSpwnFlg() { return spawn_flg; }

    int GetHp() { return hp; }

    void FalseGravity();

    void BambooAnim();

    //�F�̎擾
    ColorDate GetColorDate() { return Date; }
};

