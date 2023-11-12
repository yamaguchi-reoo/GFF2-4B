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
    int hi[3];
    int bosf[3];

    //Mの拳が降りてくるX座標
    float Magentax[10] = { 1000,100,500 };

    /*イルカ*/

    int switching;

    int bhandx;
    int bhandy;
    int down_hand;

    bool hitflg=false;
    bool onceflg=true;
    int count;
    bool Hit_Once;

    bool HitJumpAttack = false;
    bool Death_Flg = false;
    
    bool Power_Up;   //強化状態か？
    bool Rock_Once; //出現位置一度だけ格納する用

    //ボスの状態が何か受け取る
    int Boss_Form;

    int Attack_Num;//ボスの手が今何の攻撃しているか

    BossHands(int _who,Boss* boss);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);
    void HandsMagenta(GameMain* main);
    void ApplyDamage(int num);
    float GetHandsY() { return location.y; };
    float GetHandsX() { return location.x; };
};

