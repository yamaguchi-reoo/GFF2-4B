#pragma once
#include "Dxlib.h"
#include "BoxCollider.h"
#include "common.h"

struct ScrollData
{
	bool direction;
	float move;
};
class SceneScroll
{
private:
	int stage_image;	//ステージ画像(背景)
	
	float scroll_x;		//背景画像の左上頂点部のX座標
	float scroll_y;		//背景画像の左上頂点部のY座標

public:
	//コンストラクタ
	SceneScroll();
	//デストラクタ
	~SceneScroll();
	//描画以外の更新に関する処理
	void Update(Location player, float acs_l, float acs_r);
	//プレイヤーの行動範囲を固定する処理
	ScrollData PlayerScroll(Location player);
	//描画更新に関する処理
	void Draw();
};