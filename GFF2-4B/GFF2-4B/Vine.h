#pragma once
#include "BoxCollider.h"
class Vine :public BoxCollider
{
private:
	bool vine_flg; //蔓のアニメーションフラグ
	int img;       //蔓の画像

public:
	//コンストラクタ(引数:表示するX座標)
	Vine(int x);

	//デストラクタ
	~Vine();

	//更新処理
	void Update();

	//描画処理
	void Draw()const;

	//プレイヤーが強制戦闘ゾーンに閉じ込められているか(true:いる false:いない)
	bool GetVineFlg() { return vine_flg; }

	//蔓のアニメーション(下から上に)
	void VineAnimStart();

	//蔓のアニメーション(上から下に)
	void VineAnimEnd();
};

