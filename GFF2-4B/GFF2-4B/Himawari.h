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
    Himawari();
    //デストラクタ
    ~Himawari();

    void Update(GameMain* main)override;
    void Draw()const override;

    AttackData CreateAttactData();

    void Attack(GameMain* main);
    
};

