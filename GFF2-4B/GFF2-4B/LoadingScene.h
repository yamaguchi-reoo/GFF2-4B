#pragma once
#include "AbstractScene.h"

class Loading :public AbstractScene
{
private:
	int loading_image;		//読込用画像
	int loading_time;		//読込時間用変数
	int loading_mark_time;	//・(中黒点)待ち時間用変数
	//int load_mark_image;	//読込中記号表示用変数

public:
	//コンストラクタ
	Loading();
	//デストラクタ
	~Loading();

	//描画以外の更新を実装
	AbstractScene* Update()override;

	//描画に関することを実装
	void Draw()const override;
};