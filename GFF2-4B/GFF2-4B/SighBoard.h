#pragma once
#include "BoxCollider.h"

class SighBoard :
    public BoxCollider

{
private:
    Location disp_location; //チュートリアル表示位置
    int hp;             //一定回数切ると消えるように
    bool disp_flg;       //看板を出すか判断
    bool tuto_disp_flg;  //チュートリアルを出すか判断
    int disp_type;  //どの看板を出すか判断
    int sb_img[4];     //看板画像格納用
    int disp_time;  //表示時間
    bool disp_once; //看板付近にずっといたら表示が消えるように
    bool damage_once;
public:
    //コンストラクタ
    SighBoard(float pos_x, float pos_y,int type);
    //デストラクタ
    ~SighBoard();
    void Update(Location _player_location,Location _player_local_location);
    void Draw()const;

    //被弾(_num = ダメージ数)
    void ApplyDamage(int _num) { hp -= _num; }
    //一回だけ被弾するようにする
    bool GetDamageOnce() { return damage_once; }
    void SetDamageOnce(bool _flg) { damage_once = _flg; }
    //hp取得
    int GetSighBoardHp() { return hp; }
    // 
    bool GetSighFlg() { return tuto_disp_flg; }
    int GetSighTypeFlg() { return disp_type; }
};


