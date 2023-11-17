#pragma once
#include "CharaBase.h"
class Bamboo:
    public CharaBase
{
private:
    bool spawn_flg;

    bool onfloor_flg;	//いずれかの地面に触れているかどうか
    bool apply_gravity;		//重力を適用するかどうか
public:
    //コンストラクタ
    Bamboo(float pos_x, float pos_y);
    //デストラクタ
    ~Bamboo();


    void BambooReset();// 当たり判定のリセット
    //重力が働く
    void BambooGiveGravity();
    //押し出す(num = 当たっている床 _sub = 当たっている床の左上座標)
    void Push(int num, Location _sub_location, Erea _sub_erea);

    void Update(GameMain* main)override;
    void Draw()const override;

    //ダメージを受ける処理
    void ApplyDamage(int num);
    //スポーンフラグ取得
    int GetSpwanFlg() { return spawn_flg; }

    void FalseGravity();

};

