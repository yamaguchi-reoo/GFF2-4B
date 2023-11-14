#pragma once

class Score
{
private:
	int font_handle;
	int score_img;
	int total_score;
	int draw_score;

public:
	Score();
	~Score();

	void Update(); //更新処理
	void Draw()const; //描画処理
	void AddScore(int score); //スコアに加算(引数:加算するスコアの数値)
};