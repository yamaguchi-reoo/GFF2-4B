#pragma once
#include "BoxCollider.h"
#include "Scroll.h"
class Stage:
	public BoxCollider
{
private:
	int type;		//箱の種類(0=無 1=地面 2=木 3=岩 4=雲)
	bool inv_flg;		//何も描画しないか判断
	int stage_img[2];	//画像格納用
	bool end_flg[4];	//端かどうか判断
	Location draw_location[4];	//各端の描画位置
	float draw_rad[4];	//各端の描画角度
	float draw_angle;			//各端の描画角度
	bool debug_flg;		//箱の種類を表示するか
public:
	Stage(float _x, float _y, float _width, float _height,int _type);
	~Stage();
	void Update();
	void Draw()const;

	//種類を取得(0=無 1=地面 2=木 3=岩 4=雲  各オブジェクトがスポーンする位置はすべて0(判定なし)と返す)
	int GetStageCollisionType();
	//種類を設定
	void SetStageType(int _type) { type = _type; }
	//種類を取得
	int GetStageType() { return type; }
	//箱の種類を表示する
	void SetDebugFlg() { debug_flg = true; }
	//描画する画像の種類を判断する
	void SetDrawType(int up_type, int left_type, int right_type, int down_type);
};
