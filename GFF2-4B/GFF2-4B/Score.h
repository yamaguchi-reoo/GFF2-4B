#pragma once

class Score
{
private:
	int font_handle;
	int total_score;

public:
	Score();
	~Score();

	void Update(); //�X�V����
	void Draw()const; //�`�揈��
};