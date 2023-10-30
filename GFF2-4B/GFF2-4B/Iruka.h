#pragma once
#include "CharaBase.h"
class Iruka :
    public CharaBase
{
private:
    float fps_count;//フレーム

    bool attack_flg;
    bool iruka_flg; //左右移動（false = 左　true =　右）
    bool fall_flg;  //落下用フラグ
    int direction;	//顔の向き(0 = 右向き 1 = 左向き 2 = 右向き落下 3 = 左向き落下)

public:
    //コンストラクタ
    Iruka();
    //デストラクタ
    ~Iruka();

    void Update(GameMain* main)override;
    void Draw()const override;

    void Get_Fall_Flg() {
        fall_flg = true;
    }
    //攻撃をスポーンさせるのに必要な情報をまとめる
    AttackData CreateAttactData();
    void Attack(GameMain* main);
    void Stop_Attack() { attack_flg = false; }
    //ダメージ受ける処理
    void ApplyDamage(int num);

    ColorDate GetColorDate();

  
};

