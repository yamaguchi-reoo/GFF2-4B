#pragma once
#include "AbstractScene.h"
#include "DxLib.h"

class Credit :public AbstractScene
{
private:

	int credit_timer;

public:
	//コンストラクタ
	Credit();

	//デストラクタ
	~Credit();

	//描画以外の更新を実装
	AbstractScene* Update()override;

	//描画に関することを実装
	void Draw()const override;
};