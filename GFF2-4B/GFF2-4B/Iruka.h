#pragma once
#include "CharaBase.h"
 
enum  class IrukaState {
    IDLE = 0,
    RIGHT,
    LEFT,
    RIGHT_FALL,
    LEFT_FALL,
    RIGHT_RETURN,
    LEFT_RETURN
};
class Iruka :
    public CharaBase
{
private:
    IrukaState iruka_state; 

    float fps_count;//�t���[��

    bool attack_flg;//�U�����Ă��邩
    bool fall_flg;  //�����p�t���O
    bool spawn_flg;	//�X�|�[�����Ă��邩
    bool iruka_direction;
    float spawn_location_y;
    float spawn_location_x;
    bool return_flg;
        
    //�����蔻��֘A
    bool onfloor_flg[FLOOR_NUM];	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
    bool rightwall_flg;				//�����ꂩ�̉E�ǂɐG��Ă��邩�ǂ���
    bool leftwall_flg;				//�����ꂩ�̍��ǂɐG��Ă��邩�ǂ���

public:
    //�R���X�g���N�^
    Iruka(float pos_x,float pos_y,bool direction, int _who);
    //�f�X�g���N�^
    ~Iruka();

    void Update(GameMain* main)override;
    void Draw()const override;
    //���E�ړ�
    void Move(); 
    //��������
    void MoveFall();
    //���A����
    void MoveReturn();
    // �����蔻��̃��Z�b�g
    void IrukaReset();
    //�����t���O���Z�b�g
    void SetFallFlg() { fall_flg = true; }

    //�����o��(num = �������Ă��鏰 _sub = �������Ă��鏰�̍�����W)
    void Push(int num, Location _sub_location, Erea _sub_erea);
    //���ɐG��Ă��鎞�̏���(num = �������Ă��鏰 _sub = �������Ă��鏰�̒��S���W)
    void IrukaOnFloor(int num, Location _sub);

    //�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�
    AttackData CreateAttactData();
    void Attack(GameMain* main);
    void Stop_Attack() { attack_flg = false; }
    //�_���[�W�󂯂鏈��
    void ApplyDamage(int num);
    //�X�|�[���t���O�̎擾
    int GetSpwanFlg() { return spawn_flg; }

    int GetHp() { return hp; }

    ColorDate GetColorDate();
};

