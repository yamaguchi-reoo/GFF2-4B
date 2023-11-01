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
 

    IrukaState iruka_state; //向いている方向

    float fps_count;//フレーム

    bool attack_flg;
    bool fall_flg;  //落下用フラグ
    bool spawn_flg;		//スポーンしているか

public:
    //コンストラクタ
    Iruka();
    //デストラクタ
    ~Iruka();

    void Update(GameMain* main)override;
    void Draw()const override;
    void Move();
    void MoveFall();
    void MoveReturn();

    void Get_Fall_Flg() {
        fall_flg = true;
    }
    //攻撃をスポーンさせるのに必要な情報をまとめる
    AttackData CreateAttactData();
    void Attack(GameMain* main);
    void Stop_Attack() { attack_flg = false; }
    //ダメージ受ける処理
    void ApplyDamage(int num);

    int GetSpwanFlg() { return spawn_flg; }

    ColorDate GetColorDate();
};

