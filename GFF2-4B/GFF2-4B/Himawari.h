#pragma once
#include "CharaBase.h"
class Himawari :
    public CharaBase
{
private:

    bool attack_flg;    //攻撃しているか
    bool spawn_flg;	    //スポーンしているか
    bool himawari_direction;	//顔の向き(0=右向き 1=左向き)
    int attack_interval_count;

public:
    //コンストラクタ
    Himawari(float pos_x, float pos_y, bool direction, int _who);
    //デストラクタ
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

