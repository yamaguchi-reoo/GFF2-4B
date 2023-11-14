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

	void Update(); //XVˆ—
	void Draw()const; //•`‰æˆ—
	void AddScore(int score);
};