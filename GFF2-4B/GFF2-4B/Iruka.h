#pragma once
#include "CharaBase.h"
 
enum  class IrukaState {
    IDLE = 0,
    RIGHT,
    LEFT,
    RIGHT_FALL,
    LEFT_FALL,
    RIGHT_RETURN,
    LEFT_RETURN,
    DEATH,
    FALL_DEATH
};
class Iruka :
    public CharaBase
{
private:
    IrukaState iruka_state; 

    float fps_count;    //フレーム
    int anim_frame;     //アニメーションフレーム測定
    int count;          //カウント


    bool attack_flg;//攻撃しているか
    bool fall_flg;  //落下用フラグ
    bool spawn_flg;	//スポーンしているか
    bool death_flg;//死んでいるか
    bool iruka_direction; //イルカの向いている向き
    float spawn_location_y;
    float spawn_location_x;
    bool return_flg;

    int iruka_image[4];//イルカ画像
    int iruka_anim;
        
    //当たり判定関連
    bool onfloor_flg;	//いずれかの地面に触れているかどうか
    bool rightwall_flg;				//いずれかの右壁に触れているかどうか
    bool leftwall_flg;				//いずれかの左壁に触れているかどうか

public:
    //コンストラクタ
    Iruka(float pos_x,float pos_y,bool direction, int _who);
    //デストラクタ
    ~Iruka();

    void Update(GameMain* main)override;
    void Draw()const override;
    //左右移動
    void Move(); 
    //落下処理
    void MoveFall();
    //復帰処理
    void MoveReturn();
    // 当たり判定のリセット
    void IrukaReset();
    //落下フラグをセット
    void SetFallFlg() { fall_flg = true; }

    int  GetReturnFlg() { return return_flg; }

    //押し出す(_sub = 当たっている床の左上座標、幅、高さ)
    void Push(Location _sub_location, Erea _sub_erea);
    //床に触れている時の処理(num = 当たっている床 _sub = 当たっている床の中心座標)
    void IrukaOnFloor();

    //攻撃をスポーンさせるのに必要な情報をまとめる
    AttackData CreateAttactData();
    void Attack(GameMain* main);
    void Stop_Attack() { attack_flg = false; }
    //ダメージ受ける処理
    void ApplyDamage(int num);
    //スポーンフラグの取得
    int GetSpawnFlg() { return spawn_flg; }
    //hp取得
    int GetHp() { return hp; }
    //アニメーション
    void IrukaAnim();

    void SetDeathFlg(bool flg) { death_flg = flg; }

    ColorDate GetColorDate();

    void HitWall(){}
};

