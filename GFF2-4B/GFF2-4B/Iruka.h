#pragma once
#include "CharaBase.h"
 
enum  class IrukaState {
    IDLE = 0,
    RIGHT,
    LEFT,
    RIGHT_FALL,
    LEFT_FALL,
};
class Iruka :
    public CharaBase
{
private:
 

    IrukaState iruka_state; //�����Ă������

    float fps_count;//�t���[��

    bool attack_flg;
    bool fall_flg;  //�����p�t���O
    bool spawn_flg;		//�X�|�[�����Ă��邩

public:
    //�R���X�g���N�^
    Iruka();
    //�f�X�g���N�^
    ~Iruka();

    void Update(GameMain* main)override;
    void Draw()const override;
    void Move();
    void MoveFall();
    void MoveReturn();

    void Get_Fall_Flg() {
        fall_flg = true;
    }
    //�U�����X�|�[��������̂ɕK�v�ȏ����܂Ƃ߂�
    AttackData CreateAttactData();
    void Attack(GameMain* main);
    void Stop_Attack() { attack_flg = false; }
    //�_���[�W�󂯂鏈��
    void ApplyDamage(int num);

    int GetSpwanFlg() { return spawn_flg; }

    ColorDate GetColorDate();
};

