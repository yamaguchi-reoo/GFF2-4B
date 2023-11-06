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

public:
    //�R���X�g���N�^
    Himawari(float pos_x, float pos_y, bool direction, int _who);
    //�f�X�g���N�^
    ~Himawari();

    void Update(GameMain* main)override;
    void Draw()const override;

    AttackData CreateAttactData();

    void Attack(GameMain* main);

    void ApplyDamage(int num);

    int GetSpwanFlg() { return spawn_flg; }

    int GetHp() { return hp; }


    ColorDate GetColorDate();
    
};

