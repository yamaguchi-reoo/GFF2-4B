#pragma once
#include "CharaBase.h"
#include "Rock.h"

class Boss;

class BossHands :
    public CharaBase
{
private:
#define STOPBOSS (160)  //ボスが次の行動に行くまでの時間
#define IMGMAX (5)      //ボスの画像最大数
public:

    /*ザクロ拳*/
    //受け取った値によってCMYのサイズ変更用
    int hands_height[3] = { 190,190,190 };
    int hands_width[3] = { 190,190,190 };

    int Hands_img[IMGMAX];
    int Hands_Img_num;//画像切り替え用
    int hi[3];

    //Mの拳が降りてくるX座標
    float Magentax[10] = { 1000,100,500 };

    /*イルカ*/
    int Direction;  //0:左向き 1:右向き

    int switching;//拳出現位置セット用

    bool hitflg=false;
    bool onceflg=true;
    int count;

    bool HitJumpAttack = false;//ジャンプ攻撃多段ヒット防止
    bool Death_Flg = false;//HPが0になったらON
    int Death_Anim;//死亡アニメーション切り替え用
    
    bool Power_Up;   //強化状態か？
    bool Rock_Once; //岩出現位置一度だけ格納する用

    //ボスの状態が何か受け取る
    int Boss_Form;

    //どの腕を出すか用 0:マゼンタ 1:シアン 2:イエロー
    int Hands_who;

    int Attack_Num;//攻撃のデータどれ送るか識別用

    BossHands(int _who,Boss* boss);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);
    void HandsMagenta(GameMain* main);
    void HandsCyan(GameMain* main);
    void ApplyDamage(int num);
    float GetHandsY() { return location.y; };
    float GetHandsX() { return location.x; };
};

