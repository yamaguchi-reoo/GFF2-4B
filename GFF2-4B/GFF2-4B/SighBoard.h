#pragma once
#include "BoxCollider.h"

class SighBoard :
    public BoxCollider

{
private:
    Location disp_location; //チュートリアル表示位置
    bool disp_flg;  //チュートリアルを出すか判断
    int disp_type;  //どの看板を出すか判断
    int sb_img[4];     //看板画像格納用
    int disp_time;  //表示時間
public:
    //コンストラクタ
    SighBoard(float pos_x, float pos_y,int type);
    //デストラクタ
    ~SighBoard();
    void Update(Location _player_location,Location _player_local_location);
    void Draw()const;
};


