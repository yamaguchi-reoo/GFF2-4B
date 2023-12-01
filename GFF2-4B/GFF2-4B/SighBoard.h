#pragma once
#include "CharaBase.h"

class SighBoard :
    public BoxCollider

{
private:
    ColorDate Date{ 0 };
    int frame;                  //フレーム測定
    Location disp_location;     //チュートリアル表示位置
    bool disp_flg;              //看板を出すか判断
    bool tuto_disp_flg;         //チュートリアルを出すか判断
    int disp_type;              //どの看板を出すか判断
    int sb_img[4];              //看板画像格納用
    bool disp_once;             //一度表示された看板は二度と表示しないように
    int hp;                     //一定回数切ると消えるように
    bool break_flg;             //看板を破壊する
    bool direction;             //吹っ飛ぶ方向
    float acs[4];               //加速度 0=下方向 1=上方向 2=右方向 3=左方向

public:
    //コンストラクタ
    SighBoard(float pos_x, float pos_y,int type);
    //デストラクタ
    ~SighBoard();

    void Update(int _stage_height ,Location _player_location,Location _player_local_location);
    void Draw()const;

    //減速処理(num = 方向)
    void DecAcs(int num);

    //表示出来るか取得する
    bool GetDispOnce() { return disp_once; }

    //表示するかのフラグをセットする
    void SetDispOnce(bool _flg) { disp_once = _flg; }

    //チュートリアル表示中かを取得する
    bool GetDispFlg() { return tuto_disp_flg; }

    //チュートリアル表示中化を設定する
    void SetDispFlg(bool _flg) { tuto_disp_flg = _flg; }

    //どの種類の看板かを取得する
    int GetSighTypeFlg() { return disp_type; }

    //看板のHPを減らして、減らした後のHPを取得する
    int ApplyDamage(int _num) {
        hp -= _num;
        return hp;
    }

    //破壊可能にする
    void SetBreak(bool _player_direction);   

    //破壊可能フラグが立っているか判断
    bool GetBreakFlg() { return break_flg; }

    //色の取得
    ColorDate GetColorDate(){ return Date; }
};


