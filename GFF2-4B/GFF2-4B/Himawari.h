#pragma once
#include "CharaBase.h"
enum  class HimawariState {
    IDLE = 0,
    RIGHT,
    LEFT,
    RIGHT_SHOOT,
    LEFT_SHOOT,
    RIGHT_CHARGE,
    LEFT_CHARGE,
    DEATH
};

class Himawari :
    public CharaBase
{
private:
    int anim_frame;     //アニメーションフレーム測定
    int count;			//カウント
    int charge_anim_count; // チャージアニメーションのカウンタ
    HimawariState himawari_state;

    bool attack_flg;    //攻撃しているか
    bool spawn_flg;	    //スポーンしているか
    bool death_flg;     //死んでいるか
    bool himawari_direction;	//顔の向き(0=右向き 1=左向き)
    int attack_interval_count;

    //アニメーション
    int himawari_image[5];			//ザクロ画像
    int himawari_anim;				//画像アニメーション用

    int rapid_fire_interval;
    int bullet_num;
    bool charge_flg;

   int img[10];
   int num;
   int timer;

    //当たり判定関連
    bool onfloor_flg;	//いずれかの地面に触れているかどうか
    bool rightwall_flg;				//いずれかの右壁に触れているかどうか
    bool leftwall_flg;				//いずれかの左壁に触れているかどうか
    bool apply_gravity;				//重力を適用するかどうか
   
public:
    //コンストラクタ
    Himawari(float pos_x, float pos_y, bool direction, int _who);
    //デストラクタ
    ~Himawari();

    void Update(GameMain* main)override;
    void Draw()const override;

    void HimawariReset();// 当たり判定のリセット
    //重力が働く
    void HimawariGiveGravity();
    //押し出す(num = 当たっている床 _sub = 当たっている床の左上座標)
    void Push(int num, Location _sub_location, Erea _sub_erea);
    void Move();
    AttackData CreateAttactData();

    //攻撃
    void Attack(GameMain* main);
    //ダメージを受ける処理
    void ApplyDamage(int num);
    //スポーンフラグ取得
    int GetSpawnFlg() { return spawn_flg; }
    //hp取得
    int GetHp() { return hp; }

    void ReverseDirection();
    void ObverseDirection();

    void HimawariAnim();

    ColorDate GetColorDate();
    
};

