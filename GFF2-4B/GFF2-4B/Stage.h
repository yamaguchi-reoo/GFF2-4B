#pragma once
#include "BoxCollider.h"
#include "Scroll.h"
class Stage:
	public BoxCollider
{
private:
	int type;		//箱の種類(0=無 1=地面 2=木 3=岩 4=雲)
	bool debug_flg;		//箱の種類を表示するか
public:
	Stage(float _x, float _y, float _width, float _height,int _type);
	~Stage();
	void Update();
	void Draw()const;

	//ステージをずらす処理(使いやすい用にいじってもらってOK)
	void MoveStage(float _x, float _y);
	//種類を取得(0=無 1=地面 2=木 3=岩 4=雲)
	int GetStageType() { return type; }
	//種類を設定
	void SetStageType(int _type) { type = _type; }
	//箱の種類を表示する
	void SetDebugFlg() { debug_flg = true; }
};
