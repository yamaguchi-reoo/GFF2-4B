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
    int anim_frame;     //アニメーションフレーム測定
    int count;			//カウント
    BambooState bamboo_state;

    bool spawn_flg;
    bool death_flg;
    int bamboo_image[4];
    int bamboo_anim;

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
    bool ApplyDamage(int num);
    //スポーンフラグ取得
    int GetSpwnFlg() { return spawn_flg; }

    int GetHp() { return hp; }

    void FalseGravity();

    void BambooAnim();

    //色の取得
    ColorDate GetColorDate() { return Date; }
};

