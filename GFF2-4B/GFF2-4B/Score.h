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

	void Update(); //�X�V����
	void Draw()const; //�`�揈��
	void AddScore(int score); //�X�R�A�ɉ��Z(����:���Z����X�R�A�̐��l)
};