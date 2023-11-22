#pragma once
#include "BoxCollider.h"

class Koban : public BoxCollider
{
private:
	bool spawn_flg; //スポーンフラグ
	bool score_flg; //スコアを表示するかしないか
	int score_time; //スコアの表示時間
	float score_x,score_y; //スコアのX,Y座標
	int koban_img[2]; //画像用変数

public:
	Koban(/*float pos_x,float pos_y*/);  //コンストラクタ
	~Koban(); //デストラクタ

	void Update();     //更新処理
	void Draw() const; //描画処理

	//スポーンフラグをセット
	void SetSpawnFlg(bool _flg) { spawn_flg = _flg; }
	void SetReturnFlg() { spawn_flg = false; }

	//スコアフラグをセット
	void SetScoreFlg(bool _flg) { score_flg = _flg; }

	//スポーンフラグを返す
	bool GetSpawnFlg() { return spawn_flg; }

	//表示位置を設定
	void SetLocation(Location _location);

	void SetScoreLocation();
};

