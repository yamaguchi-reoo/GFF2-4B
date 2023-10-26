#pragma once
#include "Dxlib.h"
#include "BoxCollider.h"
#include "common.h"

enum class ScrollState : int
{
	INIT_POS_SCROLL = 0,
	MOVE_SCROLL
};

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

	int graph_size_x;
	int graph_size_y;

	ScrollState state;
public:
	//コンストラクタ
	SceneScroll();
	//デストラクタ
	~SceneScroll();
	//描画以外の更新に関する処理
	void Update(Location player, float acs_l, float acs_r);
	//プレイヤーの行動範囲を固定する処理
	ScrollData PlayerScroll(Location player);
	//行動範囲を越えたか判断して値を返す処理
	int ActionRangeBorder(Location player);
	//スクロールのON・OFFの切り替え処理
	void ChangeScrollMode();
	//描画更新に関する処理
	void Draw();
};