#pragma once

class Score
{
private:
	int FontHandle;
	int Score;

public:
	Score();
	~Score();

	void Update(); //�X�V����
	void Draw()const; //�`�揈��
};