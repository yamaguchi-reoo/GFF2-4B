#pragma once

class Score
{
private:
	int score_img[2];//画像用変数
	int num_img[10]; //数字画像用変数
	static int total_score; //トータルスコア
	int draw_score;  //描画用のスコア
	int temp_score[6];
	int i;

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
	static void SetScore();

	//スコアを画像に変更するための処理
	void ChangeScore();
};