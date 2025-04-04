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
    int ExplosionBig[10];//でかい爆発

    enum bosshand
    {
    };

public:
    int Count_Death;//腕が何回やられたかカウント用
    int Boss_Form;//今どの形態か 0:第一形態 1:第二形態 3:最終形態
    int Bossbody_ImgNum;//プレイヤーが今どこ側に居るか 0:右側 1:中央側 2:左側

    int timer;  //各モーションの時間
    int Explosion_ImgNum;//爆発画像切り替え用
    int Expl_count;//

    float Boss_Arm_Rightx; //右腕X座標
    float Boss_Arm_Righty; //右腕Y座標
    float Boss_Arm_Leftx; //左腕X座標
    float Boss_Arm_Lefty; //左腕Y座標

    float Boss_Body_X; //本体X座標
    float Boss_Body_Y; //本体Y座標

    float Explosion_X;
    float Explosion_Y;
    int Excount;

    int Hand_Num;
    bool New_Hand_Flg;//ボスの手を発生させる用
    int Boss_state;
    int Boss_step;
    bool Once_Flg;
    int Boss_Handmove;//ボスの手を作るときの動き用
    bool Boss_Dieflg;//ボス本体が死ぬときにtrue

    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;
    int GetBossForm() { return Boss_Form; };
    void BossImgChange(GameMain* main);
    void Boss_MakeHand();
    void ExplosionAnim();
};
