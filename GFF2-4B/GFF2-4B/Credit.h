#pragma once
#include "AbstractScene.h"
#include "DxLib.h"

class Credit :public AbstractScene
{
private:

	int end_roll01_image;
	int end_roll02_image;
	int end_roll03_image;
	int end_roll04_image;
	int end_roll05_image;
	int end_roll_makimono;
	int credit_navigation;

	int credit_timer;

	int credit_alpha;

	int alpha_sub_flg;

public:
	//コンストラクタ
	Credit();

	//デストラクタ
	~Credit();

	//描画以外の更新を実行
	AbstractScene* Update()override;

	//描画に関することを実装
	void Draw()const override;

	void ImageLoad(int& _handle, const char* _file_name);
};