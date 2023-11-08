#pragma once
#include "AbstractScene.h"

class SelectStage :public AbstractScene
{
private:
	static int stage_num;
	static int goal_flg[3]; //どこまでクリアしたか
	bool botton_flg;
	int img;

public:
	//コンストラクタ
	SelectStage();

	//デストラクタ
	~SelectStage();

	// 描画以外の更新を実装
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

	//クリアしたステージを保存
	void SetGoalFlg(int stage_num);
};

