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
public:
    //コンストラクタ
    SighBoard(float pos_x, float pos_y,int type);
    //デストラクタ
    ~SighBoard();
    void Update(Location _player_location,Location _player_local_location);
    void Draw()const;
    void SetDispOnce(bool _flg) { disp_once = _flg; }
    bool GetDispOnce() { return disp_once; }
    // 
    bool GetDispFlg() { return tuto_disp_flg; }
    void SetDispFlg(bool _flg) { tuto_disp_flg = _flg; }
    int GetSighTypeFlg() { return disp_type; }
};


