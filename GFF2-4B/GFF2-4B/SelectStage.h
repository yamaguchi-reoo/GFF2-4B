#pragma once
#include "AbstractScene.h"

class SelectStage :public AbstractScene
{
private:
	static int stage_num;
	bool botton_flg;
	int img[12];
	int Limg;
	int Stage_img[10];
	int x1, x2; //巻物アニメーション用
	int anim_flg; //巻物アニメーション用

public:
	static int goal_flg[3]; //どこまでクリアしたか

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

	//巻物のアニメーション
	void AnimMakimono(void);
};

