#pragma once
#include "CharaBase.h"
class Himawari :
    public CharaBase
{
private:

    bool attack_flg;    //�U�����Ă��邩
    bool spawn_flg;	    //�X�|�[�����Ă��邩
    bool himawari_direction;	//��̌���(0=�E���� 1=������)
    int attack_interval_count;

    //�����蔻��֘A
    bool onfloor_flg;	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
    bool rightwall_flg;				//�����ꂩ�̉E�ǂɐG��Ă��邩�ǂ���
    bool leftwall_flg;				//�����ꂩ�̍��ǂɐG��Ă��邩�ǂ���
    bool apply_gravity;				//�d�͂�K�p���邩�ǂ���
   
public:
    //�R���X�g���N�^
    Himawari(float pos_x, float pos_y, bool direction, int _who);
    //�f�X�g���N�^
    ~Himawari();

    void Update(GameMain* main)override;
    void Draw()const override;

    void HimawariReset();// �����蔻��̃��Z�b�g
    //�d�͂�����
    void HimawariGiveGravity();
    //�����o��(num = �������Ă��鏰 _sub = �������Ă��鏰�̍�����W)
    void HimawariPush(int num, Location _sub_location, Erea _sub_erea);

    AttackData CreateAttactData();

    //�U��
    void Attack(GameMain* main);
    //�_���[�W���󂯂鏈��
    void ApplyDamage(int num);
    //�X�|�[���t���O�擾
    int GetSpwanFlg() { return spawn_flg; }
    //hp�擾
    int GetHp() { return hp; }

    void ReverseDirection();
    void ObverseDirection();

    ColorDate GetColorDate();
    
};

