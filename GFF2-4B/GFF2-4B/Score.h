#pragma once

class Score
{
private:
	int score_img[2];//画像用変数
	int num_img[10]; //数字画像用変数
	static int total_score; //トータルスコア
	int draw_score;  //描画用のスコア
	static int zakuro_num; //斬ったザクロの数
	static int iruka_num;  //斬ったイルカの数
	static int himawari_num; //斬ったヒマワリの数

public:

	//コンストラクタ
	Score();

	//デストラクタ
	~Score();

	//更新処理
	void Update();

	//描画処理
	void Draw()const;

	//トータルスコアに加算(引数:加算するスコアの数値)
	void AddScore(int score);

	//スコアの値を返す
	static int GetScore() { return total_score; }

	//スコアを0に初期化
	static void ResetScore();

	//プレイヤーが斬った敵の数をカウント(0:ザクロ 1:イルカ 2:ヒマワリ)
	static void SetAttackEnemyNum(int num);

	//プレイヤーが斬った敵の数を返す(0:ザクロ 1:イルカ 2:ヒマワリ)
	static int GetAttackEnemyNum(int num);
};