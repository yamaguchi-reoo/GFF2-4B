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

    float fps_count;//フレーム

    bool attack_flg;//攻撃しているか
    bool fall_flg;  //落下用フラグ
    bool spawn_flg;	//スポーンしているか
    bool iruka_direction;
    float spawn_location_y;
    float spawn_location_x;
    bool return_flg;
        
    //当たり判定関連
    bool onfloor_flg[FLOOR_NUM];	//いずれかの地面に触れているかどうか
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

    //押し出す(num = 当たっている床 _sub = 当たっている床の左上座標)
    void Push(int num, Location _sub_location, Erea _sub_erea);
    //床に触れている時の処理(num = 当たっている床 _sub = 当たっている床の中心座標)
    void IrukaOnFloor(int num, Location _sub);

    //攻撃をスポーンさせるのに必要な情報をまとめる
    AttackData CreateAttactData();
    void Attack(GameMain* main);
    void Stop_Attack() { attack_flg = false; }
    //ダメージ受ける処理
    void ApplyDamage(int num);
    //スポーンフラグの取得
    int GetSpwanFlg() { return spawn_flg; }

    int GetHp() { return hp; }

    ColorDate GetColorDate();
};

