#pragma once
#include "BoxCollider.h"

class Koban : public BoxCollider
{
private:
	int KobanImg; //画像用変数

public:
	Koban(float pos_x,float pos_y);  //コンストラクタ
	~Koban(); //デストラクタ

	void Update();     //更新処理
	void Draw() const; //描画処理
};

