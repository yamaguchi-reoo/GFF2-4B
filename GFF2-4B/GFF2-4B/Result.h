#pragma once
#include "AbstractScene.h"

class Result :public AbstractScene
{
private:
	int score; //スコア
	int draw_score; //描画用スコア
public:
	//コンストラクタ
	Result();

	//デストラクタ
	~Result();

	// 描画以外の更新を実装
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};
