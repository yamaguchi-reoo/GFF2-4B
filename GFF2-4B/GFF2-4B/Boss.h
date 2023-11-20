#pragma once
#include "CharaBase.h"
#include "GameMain.h"

//ボス本体の状態
enum BossState {
    Boss_M=0,
    Boss_C,
    Boss_Y,
};

class Boss :
    public CharaBase
{
private:
    int Boss_MainBody[10];//ボス本体の画像
    int Boss_MainArm[10];//ボス本体腕の画像
    int Explosion[10];//爆発

    enum bosshand
    {
    };

public:
    int Count_Death;//腕が何回やられたかカウント用
    int Boss_Form;//今どの形態か 0:第一形態 1:第二形態 3:最終形態
    int Bossbody_ImgNum;//プレイヤーが今どこ側に居るか 0:右側 1:中央側 2:左側

    int timer;  //各モーションの時間

    int Boss_Arm_Rightx; //右腕X座標
    int Boss_Arm_Righty; //右腕Y座標

    int Boss_Body_X; //本体X座標
    int Boss_Body_Y; //本体Y座標

    int Hand_Num;
    bool New_Hand_Flg;//ボスの手を発生させる用
    int Boss_state;
    int Boss_step;
    bool Once_Flg;

    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;
    int GetBossForm() { return Boss_Form; };
    void BossImgChange(GameMain* main);
    void Boss_MakeHand();
};

