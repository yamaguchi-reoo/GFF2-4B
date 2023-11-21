#pragma once
#include "AbstractScene.h"
#define PI    3.1415926535897932384626433832795f

class Result :public AbstractScene
{
private:
	int score; //スコア
	int draw_score; //描画用スコア
	int img[8];//画像用変数
	int num_img[10]; //数字画像用変数
	int x1,x2; //巻物アニメーション用
	int anim_flg; //巻物アニメーション用
	int zakuro_num; //斬ったザクロの数
	int iruka_num;  //斬ったイルカの数
	int himawari_num; //斬ったヒマワリの数

public:
	//コンストラクタ
	Result();

	//デストラクタ
	~Result();

	// 描画以外の更新を実装
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

	//巻物のアニメーション
	void AnimMakimono(void);

	
};
